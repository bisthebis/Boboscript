include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/scannerlib)
set (SOURCE myexception.h parser.h parser.cpp fileast.h fileast.cpp type.h)
find_package(Qt5Core REQUIRED)

add_library(parserlib ${SOURCE})
target_link_libraries(parserlib Qt5::Core)
target_link_libraries(parserlib scannerlib)
