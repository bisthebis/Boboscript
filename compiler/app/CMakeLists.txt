include_directories(${CMAKE_SOURCE_DIR}/scannerlib)

find_package(Qt5Core REQUIRED)

add_executable(lexer main.cpp)
target_link_libraries(lexer scannerlib)
target_link_libraries(lexer Qt5::Core)