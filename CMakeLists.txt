cmake_minimum_required(VERSION 3.8)
project(UO_TOOLS)
set(CMAKE_CXX_STANDARD 17)

set(THIRD_PARTY_PATH ${PROJECT_SOURCE_DIR}/3rdparty)

add_definitions(-DASIO_STANDALONE)

include_directories(${THIRD_PARTY_PATH}/include)
# include_directories(${PROJECT_SOURCE_DIR}/tools)

link_directories(${THIRD_PARTY_PATH}/lib)

ADD_SUBDIRECTORY(queue)
ADD_SUBDIRECTORY(GenerateIterate)
ADD_SUBDIRECTORY(PlayGame)
ADD_SUBDIRECTORY(ThreadPool)
add_library(${PROJECT_NAME} main.cpp)


set(gene Generate)
set(gene_SOURCE main.cpp)

add_executable(${gene} ${gene_SOURCE})

target_link_libraries(${gene}  sixpiece  GenerateIterate)





