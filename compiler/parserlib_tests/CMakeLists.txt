include_directories(${CMAKE_SOURCE_DIR}/scannerlib ${CMAKE_SOURCE_DIR}/parserlib)

set(SOURCE main.cpp parsertest.h parsertest.cpp resources.qrc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

add_executable(parserlib_tests ${SOURCE})

target_link_libraries(parserlib_tests scannerlib)
target_link_libraries(parserlib_tests parserlib)
target_link_libraries(parserlib_tests Qt5::Core)
target_link_libraries(parserlib_tests Qt5::Test)
