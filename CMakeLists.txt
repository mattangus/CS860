cmake_minimum_required (VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

project (cs860 CXX)

find_package(OpenMP)
if(OPENMP_FOUND)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(gmp)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${cs860_SOURCE_DIR}/include)
include_directories("${GMP_INCLUDE_DIR}")

add_executable(cs860 src/main.cpp src/firstMorph.cpp src/sequence.cpp src/subwordGen.cpp)

target_link_libraries(cs860 ${GMP_LIBRARIES})

add_definitions(-std=c++11)
