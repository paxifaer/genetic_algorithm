cmake_minimum_required(VERSION 3.8)
project(Genetic)
set(CMAKE_CXX_STANDARD 11)

set(THIRD_PARTY_PATH ${PROJECT_SOURCE_DIR}/3rdparty)


add_definitions(-DASIO_STANDALONE)
add_definitions(-DORMPP_ENABLE_MYSQL)

include_directories(${THIRD_PARTY_PATH}/include)
include_directories(${PROJECT_SOURCE_DIR}/kafka)
include_directories(${PROJECT_SOURCE_DIR}/net/include)
include_directories(${PROJECT_SOURCE_DIR}/tools)

include_directories(${THIRD_PARTY_PATH}/include)

link_directories(${THIRD_PARTY_PATH}/lib)

ADD_SUBDIRECTORY(EasyThreadPool)
ADD_SUBDIRECTORY(queue)
ADD_SUBDIRECTORY(GenerateIterate)
ADD_SUBDIRECTORY(PlayGame)

add_library(${PROJECT_NAME} SHARED main.cpp )


set(gene Generate)
set(gene_SOURCE main.cpp)

add_executable(${gene} ${gene_SOURCE})

target_link_libraries(${gene}  sixpiece  GenerateIterate)





