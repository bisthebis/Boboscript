include_directories(${CMAKE_SOURCE_DIR}/scannerlib)

set(SOURCE main.cpp lexertest.h lexertest.cpp)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

add_executable(scannerlib_tests ${SOURCE})

target_link_libraries(scannerlib_tests scannerlib)
target_link_libraries(scannerlib_tests Qt5::Core)
target_link_libraries(scannerlib_tests Qt5::Test)