cmake_minimum_required(VERSION 3.8)
project(sixpiece)

add_library(${PROJECT_NAME}  SixInitialize.h SixInitialize.cpp  SixPiece.cpp SixPiece.h SixSelfPlay.cpp SixSelfPlay.h)
target_link_libraries(${PROJECT_NAME} easythreadpool GenerateIterate)

set(test SixPiece_test)
set(test_SOURCE SixPiece_test.cpp  )
add_executable(${test} ${test_SOURCE})
target_link_libraries(${test} sixpiece )


set(SelfPlay SelfPlay)
set(SelfPlay_SOURCE SixSelfPlay.cpp  SixSelfPlay.h  )
add_executable(${SelfPlay} ${SelfPlay_SOURCE})
target_link_libraries(${SelfPlay} sixpiece  )