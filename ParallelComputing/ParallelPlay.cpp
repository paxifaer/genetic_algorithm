//
// Created by Parsifal on 2022/6/27.
//
#include "ParallelPlay.h"
#include <iostream>
using namespace std;

template <class T>
class WorkerForGene : public Worker<T>
{
public:
    WorkerForGene(std::shared_ptr<T> queue) : Worker<T>(queue){};

protected:
    virtual void WorkerRun(bool original)
    {

        while (!Worker<T>::_stop)
        {
            auto e = Worker<T>::_queue->GetObjBulk();
            if (e)
            {
                while (!e->empty())
                {
                    DealElement(std::move(e->front()));
                    e->pop();
                }
            }
            else
            {
                if (!original)
                    break;
                Worker<T>::_queue->WaitComingObj();
            }
        }
    }

    virtual typename std::enable_if<std::is_same<typename T::Type, std::string>::value>::type
    DealElement(bool judge,std::string &&s)
    {

    }

    virtual typename std::enable_if<std::is_same<typename T::Type, std::string>::value>::type
    DealElement(std::string &&s)
    {
        return;
    }
};


int main()
{
    using QueueType = std::conditional_t<false, LockQueue<std::string>, FreeLockRingQueue<std::string>>;
    auto queuetask = std::shared_ptr<QueueType>(new QueueType);
    std::shared_ptr<Worker<QueueType>> worker = std::make_shared<WorkerForGene<QueueType>>(queuetask);
    std::shared_ptr<ThreadPool<QueueType>> threadpool(new ThreadPool(queuetask, worker, 2, 10));
    std::string str;
    threadpool->EnqueueStr(str);

    return 0;
}