

#include <thread>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <algorithm>




//// 线程池类
class easythreadpool
{
public:
    // 构造函数，传入线程数
    easythreadpool(size_t threads);
    // 析构
    ~easythreadpool();

    // 入队任务(传入函数和函数的参数)
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    // 一个最简单的函数包装模板可以这样写(C++11)适用于任何函数(变参、成员都可以)
    // template<class F, class... Args>
    // auto enqueue(F&& f, Args&&... args) -> decltype(declval<F>()(declval<Args>()...))
    // {    return f(args...); }
    // C++14更简单
    // template<class F, class... Args>
    // auto enqueue(F&& f, Args&&... args)
    // {    return f(args...); }

    // 停止线程池
    void stopAll();


private:
    void newThread();

private:
    std::atomic_int run_workers;   // 当前运行的工作线程数
    int             max_workers;   // 最大工作线程数
    // 任务队列
    std::queue<std::function<void()>> tasks;

    // synchronization 异步
    std::mutex              queue_mutex;   // 队列互斥锁
    std::condition_variable condition;     // 条件变量
    bool                    stop;          // 停止标志
};

// 构造函数仅启动一些工作线程
inline easythreadpool::easythreadpool(size_t threads)
        : run_workers(0)
        , max_workers(threads)
        , stop(false)
{
    if (max_workers == 0 || max_workers > (int)std::thread::hardware_concurrency()) {
        max_workers = std::thread::hardware_concurrency();
    }
}

// 添加一个新的工作任务到线程池
template<class F, class... Args>
auto easythreadpool::enqueue(F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    // 将任务函数和其参数绑定，构建一个packaged_task
    auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    // 获取任务的future
    std::future<return_type> res = task->get_future();

    size_t tasks_size = 0;
    {
        std::lock_guard<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        // 不允许入队到已经停止的线程池
        if (stop) { throw std::runtime_error("enqueue on stopped ThreadPool"); }
        // 将任务添加到任务队列
        tasks.emplace([task]() { (*task)(); });
        tasks_size = tasks.size();
    }
    // 判断当前的任务积累数，如果任务积累太多，就再创建一个线程
    if (run_workers == 0 || (tasks_size > 10 && run_workers < max_workers)) {
        newThread();   // 创建新线程
    }
    // 发送通知，唤醒某一个工作线程取执行任务
    condition.notify_one();
    return res;
}

inline easythreadpool::~easythreadpool()
{
    stopAll();
}

inline void easythreadpool::stopAll()
{
    {
        // 拿锁
        std::unique_lock<std::mutex> lock(queue_mutex);
        // 停止标志置true
        stop = true;
    }
    // 通知所有工作线程，唤醒后因为stop为true了，所以都会结束
    condition.notify_all();
    // 等待所有线程结束
    while (run_workers > 0) {
        // 如果工作线程是意外结束的，没有将 run_workers 减一，那么这里会陷入死循环
        // 所以这里也可以修改为循环一定次数后就退出，不等了
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

inline void easythreadpool::newThread()
{
    ++run_workers;   // 运行线程数加一

    std::thread thr([this]() {
        int no_task = 0;   // 用于标记任务循环
        while (true) {
            if (stop) {
                break;   // 退出线程循环
            }
            do {
                std::function<void()> task;   // 任务对象
                {
                    std::lock_guard<std::mutex> lock(this->queue_mutex);
                    // 从任务队列取出一个任务
                    if (this->tasks.empty()) {
                        ++no_task;
                        break;   // 没有任务，退出任务执行循环
                    }
                    // 取得任务队首任务(注意此处的std::move)
                    task = std::move(this->tasks.front());
                    // 从队列移除
                    this->tasks.pop();
                }
                // 执行任务
                task();

            } while (true);
            // 如果超过3次都是空循环，那么就退出线程
            if (no_task > 3) { break; }

            // 没有任务的时候，等待条件触发
            // 拿锁(独占所有权式)，队列锁也充当一下条件锁
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            // 等待条件成立(只等待180秒，条件不成立就退出)
            this->condition.wait_for(lock, std::chrono::seconds(180), [this] {
                return this->stop || !this->tasks.empty();
            });
        }   // end while
        // 线程退出的时候，从工作线程组中移除
        --run_workers;   // 运行线程数减一
    });
    thr.detach();   // 分离执行
}

//#endif   // DYNAMICTHREADPOOL_HPP




