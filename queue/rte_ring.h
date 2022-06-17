#ifndef RTE_RING_HPP
#define RTE_RING_HPP

#define RTE_CACHE_LINE_SIZE 64
#define __rte_cache_aligned __attribute__((__aligned__(RTE_CACHE_LINE_SIZE)))
#define RTE_MEMZONE_NAMESIZE 32

#include <string>
#include <mutex>
#include <queue>
#include <condition_variable>

struct rte_ring_headtail
{
    volatile unsigned int head;  /**< Prod/consumer head. */
    volatile unsigned int tail;  /**< Prod/consumer tail. */
    unsigned int single;         /**< True if single prod/cons */
};

struct rte_ring
{
    /*
    * Note: this field kept the RTE_MEMZONE_NAMESIZE size due to ABI
    * compatibility requirements, it could be changed to RTE_RING_NAMESIZE
    * next time the ABI changes
    */
    // char name[RTE_MEMZONE_NAMESIZE] __rte_cache_aligned; /**< Name of the ring. */
    int flags;               /**< Flags supplied at creation. */
    unsigned int size;           /**< Size of ring. */
    unsigned int mask;           /**< Mask (size-1) of ring. */
    unsigned int capacity;       /**< Usable size of ring */

    char pad0 __rte_cache_aligned; /**< empty cache line */

    /** Ring producer status. */
    struct rte_ring_headtail prod __rte_cache_aligned;
    char pad1 __rte_cache_aligned; /**< empty cache line */

    /** Ring consumer status. */
    struct rte_ring_headtail cons __rte_cache_aligned;
    char pad2 __rte_cache_aligned; /**< empty cache line */
};

class RTE_Ring
{
public:
    RTE_Ring(std::string name, unsigned count, unsigned single);
    ~RTE_Ring();

    unsigned int rte_ring_mp_enqueue_bulk(void * const *obj_table, unsigned int n, unsigned int *free_space);
    unsigned int rte_ring_mc_dequeue_bulk(void **obj_table, unsigned int n, unsigned int *available);

private:
    rte_ring *__ring;
    struct rte_ring *rte_ring_create(std::string name, unsigned count, unsigned single);
    int rte_ring_init(struct rte_ring *r, std::string name, unsigned count, unsigned single);
    void rte_ring_free(struct rte_ring *r);

    inline void update_tail(struct rte_ring_headtail *ht, uint32_t old_val, uint32_t new_val, uint32_t single);

    inline unsigned int __rte_ring_do_enqueue(struct rte_ring *r, void * const *obj_table, unsigned int n, unsigned int is_sp, unsigned int *free_space);
    inline unsigned int __rte_ring_move_prod_head(struct rte_ring *r, unsigned int is_sp, unsigned int n, uint32_t *old_head, uint32_t *new_head,	uint32_t *free_entries);

    inline unsigned int __rte_ring_do_dequeue(struct rte_ring *r, void **obj_table, unsigned int n, unsigned int is_sc, unsigned int *available);
    inline unsigned int __rte_ring_move_cons_head(struct rte_ring *r, int is_sc,	unsigned int n, uint32_t *old_head, uint32_t *new_head, uint32_t *entries);
};

// template <class T>
// class Stack {
//   private:
//     std::vector<T> elems;     // 元素

//   public:
//     Stack(std::string name);
//     ~Stack();
//     void push(T const&);  // 入栈
//     void pop();               // 出栈
//     T top() const;            // 返回栈顶元素
//     bool empty() const{       // 如果为空则返回真。
//         return elems.empty();
//     }
// };

// template <class T>
// Stack<T>::Stack (std::string name)
// {
//     std::cout << name << std::endl;
// }

// template <class T>
// Stack<T>::~Stack ()
// {
// }

// template <class T>
// void Stack<T>::push (T const& elem)
// {
//     // 追加传入元素的副本
//     elems.push_back(elem);
// }

// template <class T>
// void Stack<T>::pop ()
// {
//     // 删除最后一个元素
//     elems.pop_back();
// }

// template <class T>
// T Stack<T>::top () const
// {
//     // 返回最后一个元素的副本
//     return elems.back();
// }

#endif //RTE_RING_HPP