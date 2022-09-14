project(sixpiece)

add_library(${PROJECT_NAME} SixPiece.cpp SixPiece.h)

target_link_libraries(${PROJECT_NAME} easythreadpool GenerateIterate)