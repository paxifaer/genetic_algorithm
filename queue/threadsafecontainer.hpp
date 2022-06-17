#pragma once

#include<mutex>
#include<queue>
#include<functional>
#include <optional>

template<typename T>
class custom_priority_queue : public std::priority_queue<T> {
public:
    template <typename Pred>
    bool contains_if(Pred pred) const 
    {
        auto it = std::find_if(this->c.begin(), this->c.end(), pred);
        return it != this->c.end();
    }

    template <typename Pred>
    bool remove_if(Pred pred) 
    {
        const auto old_size = this->size();
        this->c.erase(std::remove_if(this->c.begin(), this->c.end(), pred), this->c.end());
        if (old_size == this->size()) return false;
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
    }
};

template<typename T>
class ThreadSafePriorityQueue
{
private:
    std::mutex __mutex;
    custom_priority_queue<T> __queue;
    std::condition_variable_any __notempty;
public:
    void AddObj(const T &t)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __queue.emplace(t);
        __notempty.notify_one();
    }

    bool GetObj(T &obj, std::function<bool(T)>comparefun=nullptr)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __notempty.wait(lck, [this]{return !__queue.empty();});
        if(comparefun && !comparefun(__queue.top()))
            return false;
        obj = __queue.top();
        __queue.pop();
        return true;
    }

    bool GetObj(std::queue<T>& queue)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __notempty.wait(lck, [this]{return !__queue.empty();});
        queue = std::move(__queue);
        return true;
    }

    bool GetTopObj(T &obj)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        if(!__queue.empty())
        {
            obj = __queue.top();
            return true;
        }
        else
            return false;
    }

    void DeleteObj(std::function<bool(T)>comparefun)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __queue.remove_if(comparefun);
    }
};

template <typename T>
class [[deprecated]] ThreadSafeQueue
{
public:
    explicit ThreadSafeQueue(uint16_t capacity=2048):__capacity(capacity){}
    ~ThreadSafeQueue() = default;

    bool AddObj(const T &t)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        if(__queue.size()<__capacity)
        {
            __queue.emplace(t);
            __notempty.notify_one();
            return true;
        }
        else
            return false;
    }

    bool GetObj(T &obj, std::function<bool(T)>comparefun=nullptr)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __notempty.wait(lck, [this]{return !__queue.empty();});
        if(comparefun && !comparefun(__queue.front()))
            return false;
        obj = __queue.front();
        __queue.pop();
        return true;
    }

    bool GetObj(std::queue<T>& queue)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __notempty.wait(lck, [this]{return !__queue.empty();});
        queue = std::move(__queue);
        return true;
    }

    uint32_t GetQueueSize()
    {
        std::unique_lock<std::mutex> lck(__mutex);
        return __queue.size();
    }
    
private:
    std::mutex __mutex;
    std::queue<T> __queue;
    uint16_t __capacity;
    std::condition_variable_any __notempty;
};

template<class T, unsigned int SIZE=2048>
class LockQueue
{
public:
    using Type=T;
    LockQueue()=default;

    LockQueue& operator = (const LockQueue& other) = delete;

    virtual ~LockQueue()=default;

    unsigned int GetElementNums()
    {
        return __queue.size();
    }

    bool AddObj(T &&t)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        if(__queue.size() < __capacity)
        {
            __queue.emplace(std::move(t));
            __consumer.notify_one();
            return true;
        }
        else
            return false;
    }

    template <class C> 
    bool AddObjBulk(C &&v)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        if(v.size() + __queue.size() < __capacity)
        {
            for(auto &&element:v)
                __queue.emplace(std::move(element));
            __consumer.notify_one();
            return true;
        }
        else
            return false;
    }

    std::optional<T> GetObj(std::function<bool(T)>comparefun=nullptr)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        if(!__queue.empty())
        {
            if(comparefun && !comparefun(__queue.front()))
                return std::nullopt;
            else
            {
                auto obj = std::move(__queue.front());
                __queue.pop();
                return obj;
            }
        }
        else
            return std::nullopt;
    }

    std::optional<std::queue<T>> GetObjBulk(unsigned int n = 0)
    {
        std::unique_lock<std::mutex> lck(__mutex);
        if(!__queue.empty())
        {
            std::queue<T> q;
            swap(q,__queue);
            return q;
        }
        else
            return std::nullopt;
    }

    bool IsEmpty()
    {
        std::unique_lock<std::mutex> lck(__mutex);
        return __queue.empty();
    }

    void WaitComingObj()
    {
        std::unique_lock<std::mutex> lck(__mutex);
        __consumer.wait(lck,[this](){return GetElementNums();});
    }
    
private:
    std::mutex __mutex;
    std::condition_variable __consumer;
    std::queue<T> __queue;
    uint16_t __capacity = SIZE;
};