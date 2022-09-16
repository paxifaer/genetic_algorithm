cmake_minimum_required(VERSION 3.8)
project(easythreadpool)
set(CMAKE_CXX_STANDARD 11)
add_library(${PROJECT_NAME}  SHARED easythreadpool.cpp easythreadpool.h)

#set_target_properties(easythreadpool PROPERTIES LINKER_LANGUAGE CXX)