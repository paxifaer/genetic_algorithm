project(sixpiece)

add_library(${PROJECT_NAME} SHARED SixPiece.cpp SixPiece.h)
target_link_libraries(${PROJECT_NAME} easythreadpool GenerateIterate)
set(test SixPiece_test)
set(test_SOURCE SixPiece_test.cpp)
add_executable(${test} ${test_SOURCE})
target_link_libraries(${test} sixpiece)
