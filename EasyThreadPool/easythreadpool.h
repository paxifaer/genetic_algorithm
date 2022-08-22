//
// Created by Parsifal on 2022/8/22.
//

#ifndef GENETIC_EASYTHREADPOOL_H
#define GENETIC_EASYTHREADPOOL_H
#include <iostream>
#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>
#include <future>
#include <atomic>
#include <vector>
#include <queue>

#include <unistd.h>

using namespace std;

class threadpool
{
private:
    mutex m_task;
    condition_variable cv_task;
    using Task = function<void()>;
    atomic<bool>stop;
    queue<Task>queue;
    vector<thread> pool;
public:
    threadpool(size_t t)
    {
        for(int i=0;i<t;i++)
        {
            pool.emplace_back(&threadpool::schedual,this);
        }
    }

    template<class F,class ...Args>
    auto commit(F&&f,Args&&...args)-> future<decltype(f(args...))> {
        if(stop.load()){    // stop == true ??
            throw std::runtime_error("task executor have closed commit.");
        }

        using Restype = decltype(f(args...));
        auto task = make_shared<packaged_task<Restype()>>(bind(forward<F>(f), forward<Args>(args)...));
        {
            unique_lock<mutex> lock{m_task};
            queue.template emplace([task]() {
                (*task)();
            });
        }
        cv_task.notify_all();
        future<Restype> future = task->get_future();
        return future;
    }
    void shutdown(){
        this->stop.store(true);
    }

    // 重启任务提交
    void restart(){
        this->stop.store(false);
    }


    ~threadpool(){
        for(int i=0;i<pool.size();i++)
        {
            pool[i].join();
        }
    }
private:
    Task get_one_task()
    {
        unique_lock<mutex>lock{m_task};
        cv_task.wait(lock,[this](){return !queue.empty();});
        Task now_task = queue.front();
        queue.pop();
        return now_task;
    }
    void schedual()
    {   //while(true)
        {
            while (Task task = get_one_task()) {
                task();
            }
        }
    }

};
#endif //GENETIC_EASYTHREADPOOL_H
