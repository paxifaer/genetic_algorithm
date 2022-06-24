project(ParallelComputing)

add_library(${PROJECT_NAME} ParallelPlay.cpp ParallelPlay.h)

set(Parallel_Computing ${PROJECT_NAME})
set(Parallel_Computing_SOURCE ParallelPlay.cpp)
add_executable(${Parallel_Computing}  ${Parallel_Computing_SOURCE} )
target_link_libraries(${PROJECT_NAME} threadpool )