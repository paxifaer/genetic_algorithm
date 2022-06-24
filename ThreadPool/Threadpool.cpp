#include "Threadpool.hpp"
#include <vector>
#include <string>
#include <memory>

#define SPDLOG_FILENAME "log/TrimuleLogger.log"
#define SPDLOGGERNAME "TrimuleLogger"
#define LOGGER spdlog::get(SPDLOGGERNAME)



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

