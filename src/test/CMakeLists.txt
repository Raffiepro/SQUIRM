INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
file(GLOB SOURCES
    */*.h
    */*.cpp
    *.h
    *.cpp
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_LIBS "-O3 -fpic -shared") # Perque corri això

add_library(test SHARED ${SOURCES} ${PROJECT_SOURCE_DIR}/src/api/wyrm.h)

install( TARGETS base DESTINATION lib )