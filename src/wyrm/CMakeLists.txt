INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
file(GLOB SOURCES
    */*.h
    */*.cpp
    *.h
    *.cpp
)

file(GLOB ../api/wyrm)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wyrm ${SOURCES} ${PROJECT_SOURCE_DIR}/src/api/wyrm.h)

target_link_libraries(Wyrm gmp)
target_link_libraries(Wyrm libdl.so)
