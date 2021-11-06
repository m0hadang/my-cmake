cmake_minimum_required(VERSION 3.2)

set(This Tester)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

set(Sources
  hello-test.cpp
  fixture-test.cpp
  sweet-fixture-test.cpp
  stub-test.cpp
  time-set-test.cpp
  mock-expect-test.cpp
  mock-oncall-test.cpp
)

add_executable(${This} ${Sources})

if(MSVC)
  set_property(TARGET ${This} PROPERTY
              MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

             
target_link_libraries(${This} PUBLIC
  gtest_main
  gmock_main
  Markov
)

add_test(
  NAME ${This}
  COMMAND ${This}
)