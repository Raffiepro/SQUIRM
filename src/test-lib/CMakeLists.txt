INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
file(GLOB SOURCES
    */*.h
    */*.cpp
    *.h
    *.cpp
    ${PROJECT_SOURCE_DIR}/src/api/*.h
)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_LIBS "-O3 -fPIC -shared") # Perque corri això

add_library(test-lib SHARED ${SOURCES} ${PROJECT_SOURCE_DIR}/src/wyrm.h)

install(TARGETS base DESTINATION lib )
