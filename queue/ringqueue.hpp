#pragma once

#include<iostream>
#include<array>
#include<memory>
#include<vector>
#include<atomic>
#include<tuple>
#include<algorithm>
#include<queue>
#include<type_traits>
#include <optional>
#include"../public/tsglobal.hpp"
#include <mutex>
#include <condition_variable>
template<class T, unsigned int SIZE=2048>
class FreeLockRingQueue
{
private:
    std::mutex __mutex;
    std::condition_variable __consumer;
    struct RingHeadTail
    {
        std::atomic<unsigned int> head;
        std::atomic<unsigned int> tail;
    };

    struct RingInfo
    {
        bool single;
        unsigned int size;
        unsigned int mask;
        unsigned int capacity;
        RingHeadTail prod;
        RingHeadTail cons;
    };

    RingInfo ringinfo;
    std::array<T, CheckSize<SIZE>::value> array;

    void InitRingFreeLockQueue(unsigned int size, bool single)
    {
        ringinfo.single = single;

        ringinfo.size = size;
        ringinfo.capacity = ringinfo.mask = size-1;

        ringinfo.prod.head = ringinfo.cons.head = 0;
        ringinfo.prod.tail = ringinfo.cons.tail = 0;
    }

    std::tuple<bool, unsigned int, unsigned int> MoveProdHead(size_t n)
    {
        int success = 0;
        unsigned int old_head,new_head = 0;
        while (success == 0)
        {
            old_head = ringinfo.prod.head.load();
            auto free_entries = ringinfo.capacity + ringinfo.cons.tail.load() - old_head;
            if (n > free_entries)
                return std::tuple<bool, unsigned int, unsigned int>(false,0,0);

            new_head = old_head + n;
            if (ringinfo.single)
            {
                ringinfo.prod.head = new_head;
                success = 1;
            }
            else
                success = ringinfo.prod.head.compare_exchange_weak(old_head, new_head);
        }
        return std::tuple<bool, unsigned int, unsigned int>{true, old_head, new_head};
    }

    std::tuple<bool, unsigned int, unsigned int> MoveConsHead(unsigned int &n)
    {
        int success = 0;
        unsigned int old_head,new_head = 0;
        while (success == 0)
        {
            old_head = ringinfo.cons.head.load();
            auto entries = ringinfo.prod.tail.load() - old_head;
            n = std::min(entries, n);
            if( n == 0)
                return std::tuple<bool, unsigned int, unsigned int>{false, old_head, new_head};

            new_head = old_head + n;
            if (ringinfo.single)
            {
                ringinfo.cons.head = new_head;
                success = 1;
            }
            else
                success = ringinfo.cons.head.compare_exchange_weak(old_head, new_head);
        }
        return std::tuple<bool, unsigned int, unsigned int>{true, old_head, new_head};
    }

    void AddItems(unsigned int old_head, std::vector<T> &&v)
    {
        const unsigned int size = ringinfo.size;
        unsigned int idx = old_head & ringinfo.mask;
        if( idx + v.size() < size)
        {
            for(auto &&item : v)
                array[idx++] = std::move(item);
        }
        else
        {
            unsigned int i;
            for (i = 0; idx < size; i++, idx++)
                array[idx] = v[i];
            for (idx = 0; i < v.size(); i++, idx++)
                array[idx] = v[i];
        }
    }

    template <class C>
    std::optional<C> GetObjBulk(unsigned int n)
    {
        C t;
        auto [flag, old_head, new_head] = MoveConsHead(n);
        if(!flag)
            return std::nullopt;
        else
        {
            t = std::move(GetItems<C>(old_head, n));
            UpdateTail(ringinfo.cons, old_head, new_head);
            return t;
        }
    }

    ////////////////////任意类型/////////////////////////
    template <class C>
    typename std::enable_if<is_specialization_of<typename std::decay<C>::type, std::vector>::value, C>::type
    GetItems(unsigned int old_head, unsigned int n)
    {
        return GetItems<C>([](auto &&v, auto &&element)
                           {
                               v.emplace_back(std::move(element));
                           }, old_head, n);
    }

    template <class C>
    typename std::enable_if<is_specialization_of<typename std::decay<C>::type, std::queue>::value, C>::type
    GetItems(unsigned int old_head, unsigned int n)
    {
        return GetItems<C>([](auto &&v, auto &&element)
                           {
                               v.emplace(std::move(element));
                           }, old_head, n);
    }
    ////////////////////任意类型/////////////////////////

    template <class C, class F>
    decltype(auto) GetItems(F &&f, unsigned int old_head, unsigned int n)
    {
        C v;
        const unsigned int size = ringinfo.size;
        unsigned int idx = old_head & ringinfo.mask;
        if( idx + n < size)
        {
            for(unsigned int i = 0; i < n; i++)
                f(v, std::move(array[idx+i]));
        }
        else
        {
            unsigned int i;
            for (i = 0; idx < size; i++, idx++)
                f(v, std::move(array[idx]));
            for (idx = 0; i < n; i++, idx++)
                f(v, std::move(array[idx]));
        }
        return v;
    }

    void UpdateTail(RingHeadTail &ht, unsigned int old_val, unsigned int new_val)
    {
        ///////error////////////////
        // while(!ht.tail.compare_exchange_weak(old_val, new_val,std::memory_order_consume))
        // {}
        ///////error////////////////

        if (!ringinfo.single)
            while (ht.tail.load() != old_val){}
        ht.tail.store(new_val,std::memory_order_release);

        ////err//////////////////////
        // ht.tail.fetch_add(new_val-old_val);
        ////err//////////////////////
    }
public:
    using Type=T;
    FreeLockRingQueue()
    {
        InitRingFreeLockQueue(CheckSize<SIZE>::value, false);
    };

    FreeLockRingQueue& operator = (const FreeLockRingQueue& other) = delete;

    virtual ~FreeLockRingQueue()=default;

    unsigned int GetElementNums()
    {
        return ringinfo.prod.tail.load() - ringinfo.cons.head.load();
    }

    bool AddObj(T &&t)
    {
        std::vector<T> v;
        v.emplace_back(std::move(t));
        return AddObjBulk(std::move(v));
    }

    template <template<class, class> class C, class A>
    bool AddObjBulk(C<T, A> &&v)
    {
        auto [flag, old_head, new_head] = MoveProdHead(v.size());
        if(!flag)
            return false;
        else
        {
            AddItems(old_head, std::move(v));
            UpdateTail(ringinfo.prod, old_head, new_head);
            __consumer.notify_one();
            return true;
        }
    }

    std::optional<T> GetObj()
    {
        auto e1 = GetObjBulk<std::vector>(1);
        if(e1)
            return e1->front();
        else
            return std::nullopt;
    }

    std::optional<std::queue<T>> GetObjBulk(unsigned int n = 10)
    {
        auto e1 = GetObjBulk<std::queue>(n);
        if(e1)
            return e1;
        else
            return std::nullopt;
    }

    ////////////////////任意类型/////////////////////////
    template <template<class, class> class C, class A=std::allocator<T>>
    std::optional<typename std::enable_if<std::is_same<C<T, A>,std::vector<T>>::value, C<T,A>>::type>
    GetObjBulk(unsigned int n)
    {
        return GetObjBulk<C<T, A>>(n);
    }

    template <template<class> class C>
    std::optional<typename std::enable_if<std::is_same<C<T>,std::queue<T>>::value, C<T>>::type>
    GetObjBulk(unsigned int n)
    {
        return GetObjBulk<C<T>>(n);
    }
    ////////////////////任意类型/////////////////////////

    void WaitComingObj()
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __consumer.wait(lck,[this](){return GetElementNums();});
    }


};