cmake_minimum_required(VERSION 3.11)
project(utest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUNIT_TEST -I../src -Wall -Wextra -Wno-long-long -pedantic -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNIT_TEST -I../src -Wall -Wextra -Wno-long-long -pedantic -pthread")

add_executable(utest
  ./src/utest.cpp
  ./src/CTraditionalThread.cpp
  ./src/CSampleThread.cpp
)


