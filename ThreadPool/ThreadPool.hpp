#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include "../queue/threadsafecontainer.hpp"
#include "../queue/ringqueue.hpp"
#include <atomic>

template<typename T>
class GetContainerType;

template<typename T>
struct GetContainerType<LockQueue<T>>
{
typedef T Type;
};

template<typename T>
struct GetContainerType<FreeLockRingQueue<T>>
{
typedef T Type;
};

template<class T>
class Worker
{
public:
    using ContainerType = typename T::Type;
    // using ContainerType = typename GetContainerType<T>::Type;
    Worker(std::shared_ptr<T> queue):_queue(queue) {}
    void CreateWorker(bool original)
    {
        WorkerRun(original);
    }

protected:
    std::shared_ptr<T> _queue;
    bool _stop = false;
    virtual void WorkerRun(bool original)
    {
        while(!_stop)
        {
            auto e = _queue->GetObjBulk();
            if(e)
            {
                while(!e->empty())
                {
                    DealElement(std::move(e->front()));
                    e->pop();
                }
            }
            else
            {
                if(!original)
                    break;
                _queue->WaitComingObj();
            }
        }

    }
    virtual void DealElement(ContainerType &&p) = 0;
};


template<class QueueType>
class ThreadPool
{
public:
    ThreadPool(size_t minsize, size_t maxsize=10):__minsize(minsize),__maxsize(maxsize)
    {
        if(!__queuetask)
            __queuetask = std::shared_ptr<QueueType>(new QueueType);

        if(!__worker)
            __worker = std::make_shared<WorkerDefault>(__queuetask);

        for(size_t i = 0;i<__minsize;++i)
            __workerthreads.emplace_back(std::move(CreateWorker(true)));
    }

    ThreadPool(std::shared_ptr<QueueType> queuetask, std::shared_ptr<Worker<QueueType>> worker, size_t minsize, size_t maxsize=10):
            __queuetask(queuetask),__worker(worker),__minsize(minsize),__maxsize(maxsize)
    {
        for(size_t i = 0;i<__minsize;++i)
            __workerthreads.emplace_back(std::move(CreateWorker(true)));
    }

    template<class F, class... Args>
    auto EnqueueFun(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        // with -std=c++2b you can also code as:
        // auto task = std::packaged_task<return_type()>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        // while(!__queuetask.AddObj([task=std::move(task)]()mutable{ (*task)(); }))
        // {...}

        auto task = std::make_shared< std::packaged_task<return_type()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        while(!__queuetask->AddObj([task](){ (*task)(); }))
        {
            if(__totalnum < __maxsize)
                CreateWorker(false).detach();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        return res;
    }

    template<class T>
    void EnqueueStr(T&& t)
    {
        while(!__queuetask->AddObj(std::move(t)))
        {
            if(__totalnum < __maxsize)
                CreateWorker(false).detach();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    ~ThreadPool()
    {
        for(std::thread &worker: __workerthreads)
            worker.join();
    }

private:
    size_t __minsize;
    size_t __maxsize;
    std::atomic<unsigned int> __totalnum;
    std::vector< std::thread > __workerthreads;
    std::shared_ptr<Worker<QueueType>> __worker;
    std::shared_ptr<QueueType> __queuetask;

    class WorkerDefault:public Worker<QueueType>
    {
    public:
        WorkerDefault(std::shared_ptr<QueueType> queue):Worker<QueueType>(queue){};

    protected:
        virtual void DealElement(std::function<void()> &&p) final
        {
            p();
        }
    };

    std::thread CreateWorker(bool original)
    {
        std::thread t( [this,original]
                       {
                           __totalnum++;
                           __worker->CreateWorker(original);
                           __totalnum--;
                       });

        return t;
    }
};