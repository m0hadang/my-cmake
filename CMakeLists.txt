cmake_minimum_required(VERSION 3.2)

set(This markov)
cmake_policy(SET CMP0091 NEW)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)



include_directories(
  include
)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS
  src/*.cc
)

if(BUILD_STATIC)
  set(MARKOV_LIBRARY_TYPE STATIC)  
  set(MARKOV_API_TYPE BUILD_STATIC)
else()
  set(BUILD_SHARED on)
  set(MARKOV_LIBRARY_TYPE SHARED)
  set(MARKOV_API_TYPE BUILD_SHARED)
endif()

add_library(${This} ${MARKOV_LIBRARY_TYPE}
  ${Sources}
)

add_executable(example
  main.cc
)

target_link_libraries(example
  ${This}
)

add_compile_definitions(${MARKOV_API_TYPE})

if(BUILD_RUNTIMESTATIC AND MSVC)
  set_property(TARGET ${This} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set_property(TARGET example PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

endif()

if(BUILD_TEST)
  add_library(markov-test STATIC
    ${Sources}
  )

  enable_testing()
  add_subdirectory(googletest)
  add_subdirectory(test)
endif()