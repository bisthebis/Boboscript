include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set (SOURCE command_line.cpp command_line.h myexception.h scanner.cpp scanner.h token.cpp token.h)
find_package(Qt5Core REQUIRED)

add_library(scannerlib ${SOURCE})
target_link_libraries(scannerlib Qt5::Core)