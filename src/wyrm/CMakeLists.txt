INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
file(GLOB SOURCES
    */*.h
    */*.cpp
    */*.c
    *.h
    *.cpp
    *.c
    ${PROJECT_SOURCE_DIR}/src/api/*.h
)

file(GLOB ../wyrm.h)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wyrm ${SOURCES} ${PROJECT_SOURCE_DIR}/src/wyrm.h)

if (NOT WIN32)
    target_link_libraries(Wyrm libdl.so)
endif ()
