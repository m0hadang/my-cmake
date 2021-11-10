cmake_minimum_required(VERSION 3.2)

set(This mohadang-markov)
cmake_policy(SET CMP0091 NEW)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

include_directories(
  include
)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS
  src/*.cc
)

add_library(${This} STATIC
  ${Sources}
)

add_executable(example
  main.cc
)

target_link_libraries(example
  ${This}
)

add_subdirectory(test)