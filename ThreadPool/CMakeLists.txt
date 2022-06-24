project(threadpool)

add_library(${PROJECT_NAME}  Threadpool.cpp ThreadPool.hpp)


set(POOL threadpool)
set(POOL_SOURCE Threadpool.cpp ThreadPool.hpp)
target_link_libraries(${POOL}    uoqueue)
