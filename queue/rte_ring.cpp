#include <iostream>
#include "rte_ring.h"

#define POWEROF2(x) ((((x)-1) & (x)) == 0)
#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)
#define RTE_RING_SZ_MASK  (unsigned)(0x0fffffff) /**< Ring size mask */
#define RING_F_EXACT_SZ 0x0004

#define ENQUEUE_PTRS(r, ring_start, prod_head, obj_table, n, obj_type) do { \
	unsigned int i; \
	const uint32_t size = (r)->size; \
	uint32_t idx = prod_head & (r)->mask; \
	obj_type *ring = (obj_type *)ring_start; \
	if (likely(idx + n < size)) { \
		for (i = 0; i < (n & ((~(unsigned)0x3))); i+=4, idx+=4) { \
			ring[idx] = obj_table[i]; \
			ring[idx+1] = obj_table[i+1]; \
			ring[idx+2] = obj_table[i+2]; \
			ring[idx+3] = obj_table[i+3]; \
		} \
		switch (n & 0x3) { \
		case 3: \
			ring[idx++] = obj_table[i++]; /* fallthrough */ \
		case 2: \
			ring[idx++] = obj_table[i++]; /* fallthrough */ \
		case 1: \
			ring[idx++] = obj_table[i++]; \
		} \
	} else { \
		for (i = 0; idx < size; i++, idx++)\
			ring[idx] = obj_table[i]; \
		for (idx = 0; i < n; i++, idx++) \
			ring[idx] = obj_table[i]; \
	} \
} while (0)

#define DEQUEUE_PTRS(r, ring_start, cons_head, obj_table, n, obj_type) do { \
	unsigned int i; \
	uint32_t idx = cons_head & (r)->mask; \
	const uint32_t size = (r)->size; \
	obj_type *ring = (obj_type *)ring_start; \
	if (likely(idx + n < size)) { \
		for (i = 0; i < (n & (~(unsigned)0x3)); i+=4, idx+=4) {\
			obj_table[i] = ring[idx]; \
			obj_table[i+1] = ring[idx+1]; \
			obj_table[i+2] = ring[idx+2]; \
			obj_table[i+3] = ring[idx+3]; \
		} \
		switch (n & 0x3) { \
		case 3: \
			obj_table[i++] = ring[idx++]; /* fallthrough */ \
		case 2: \
			obj_table[i++] = ring[idx++]; /* fallthrough */ \
		case 1: \
			obj_table[i++] = ring[idx++]; \
		} \
	} else { \
		for (i = 0; idx < size; i++, idx++) \
			obj_table[i] = ring[idx]; \
		for (idx = 0; i < n; i++, idx++) \
			obj_table[i] = ring[idx]; \
	} \
} while (0)

RTE_Ring::RTE_Ring(std::string name, unsigned count, unsigned single)
{
    __ring = rte_ring_create(name, count, single);
}

RTE_Ring::~RTE_Ring()
{
    rte_ring_free(__ring);
}


rte_ring* RTE_Ring::rte_ring_create(std::string name, unsigned count, unsigned single)
{
    unsigned int ring_size;

    /* count must be a power of 2 */
    if ((!POWEROF2(count)) || (count > RTE_RING_SZ_MASK )) {
        return nullptr;
    }

    ring_size = count * sizeof(void *) + sizeof(struct rte_ring);
    rte_ring *r = (rte_ring *) new char[ring_size];
    if (r != nullptr)
        rte_ring_init(r, std::move(name), count, single);
    return r;
}

int RTE_Ring::rte_ring_init(struct rte_ring *r, std::string name, unsigned count, unsigned single)
{
    /* init the ring structure */
    r->flags = single;
    r->prod.single = single;
    r->cons.single = single;

    r->size = count;
    r->mask = count - 1;
    r->capacity = r->mask;

    r->prod.head = r->cons.head = 0;
    r->prod.tail = r->cons.tail = 0;

    return 0;
}

void RTE_Ring::rte_ring_free(struct rte_ring *r)
{
    delete r;
}

unsigned int RTE_Ring::rte_ring_mp_enqueue_bulk(void * const *obj_table, unsigned int n, unsigned int *free_space)
{
    bool is_sp = false;
    return __rte_ring_do_enqueue(__ring, obj_table, n, is_sp, free_space);
}

inline unsigned int RTE_Ring::__rte_ring_do_enqueue(struct rte_ring *r, void * const *obj_table,
                                                    unsigned int n, unsigned int is_sp, unsigned int *free_space)
{
    uint32_t prod_head, prod_next;
    uint32_t free_entries;

    n = __rte_ring_move_prod_head(r, is_sp, n, &prod_head, &prod_next, &free_entries);
    if(n)
    {
        ENQUEUE_PTRS(r, &r[1], prod_head, obj_table, n, void *);

        update_tail(&r->prod, prod_head, prod_next, is_sp);
    }
    return n;
}

inline unsigned int RTE_Ring::__rte_ring_move_prod_head(struct rte_ring *r, unsigned int is_sp,
                                                        unsigned int n, uint32_t *old_head, uint32_t *new_head,	uint32_t *free_entries)
{
    const uint32_t capacity = r->capacity;
    unsigned int max = n;
    int success;

    do {
        /* Reset n to the initial burst count */
        n = max;

        *old_head = __atomic_load_n(&r->prod.head,
                                    __ATOMIC_ACQUIRE);

        *free_entries = (capacity + r->cons.tail - *old_head);

        /* check that we have enough room in ring */
        if (unlikely(n > *free_entries))
            return 0;

        *new_head = *old_head + n;
        if (is_sp)
            r->prod.head = *new_head, success = 1;
        else
            success = __atomic_compare_exchange_n(&r->prod.head,
                                                  old_head, *new_head,
                                                  0, __ATOMIC_ACQUIRE,
                                                  __ATOMIC_RELAXED);
    } while (unlikely(success == 0));
    return n;
}

inline void RTE_Ring::update_tail(struct rte_ring_headtail *ht, uint32_t old_val, uint32_t new_val, uint32_t single)
{
    /*
     * If there are other enqueues/dequeues in progress that preceded us,
     * we need to wait for them to complete
     */
    if (!single)
        while (unlikely(ht->tail != old_val)){}

    __atomic_store_n(&ht->tail, new_val, __ATOMIC_RELEASE);
}

unsigned int RTE_Ring::rte_ring_mc_dequeue_bulk(void **obj_table, unsigned int n, unsigned int *available)
{
    bool is_sp = false;
    return __rte_ring_do_dequeue(__ring, obj_table, n, is_sp, available);
}

inline unsigned int RTE_Ring::__rte_ring_do_dequeue(struct rte_ring *r, void **obj_table, unsigned int n, unsigned int is_sc, unsigned int *available)
{
    uint32_t cons_head, cons_next;
    uint32_t entries;

    n = __rte_ring_move_cons_head(r, (int)is_sc, n, &cons_head, &cons_next, &entries);

    if(n)
    {
        DEQUEUE_PTRS(r, &r[1], cons_head, obj_table, n, void *);

        update_tail(&r->cons, cons_head, cons_next, is_sc);
    }
    return n;
}

inline unsigned int RTE_Ring::__rte_ring_move_cons_head(struct rte_ring *r, int is_sc,	unsigned int n, uint32_t *old_head, uint32_t *new_head,	uint32_t *entries)
{
    unsigned int max = n;
    int success;

    /* move cons.head atomically */
    do {
        /* Restore n as it may change every loop */
        n = max;
        *old_head = __atomic_load_n(&r->cons.head,
                                    __ATOMIC_ACQUIRE);

        *entries = (r->prod.tail - *old_head);

        /* Set the actual entries for dequeue */
        if (unlikely(n > *entries))
            return 0;

        *new_head = *old_head + n;
        if (is_sc)
            r->cons.head = *new_head, success = 1;
        else
            success = __atomic_compare_exchange_n(&r->cons.head,
                                                  old_head, *new_head,
                                                  0, __ATOMIC_ACQUIRE,
                                                  __ATOMIC_RELAXED);
    } while (unlikely(success == 0));
    return n;
}