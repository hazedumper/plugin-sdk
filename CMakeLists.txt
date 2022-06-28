set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(HAZEDUMPER_PROJECT_NAME "hazedumper-plugin-sdk")

cmake_minimum_required(VERSION 3.15)
project(${HAZEDUMPER_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++20")

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  set(LUA_INCLUDE "/usr/include/luajit-2.1")
endif ()

include_directories(
  ${LUA_INCLUDE}
  "${PROJECT_SOURCE_DIR}/include"
)

file(GLOB SOURCES "src/**/*.cpp")
set(PROJECT_LINK_LIBS pthread dl luajit-5.1)

add_library(${HAZEDUMPER_PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${HAZEDUMPER_PROJECT_NAME} PRIVATE ${PROJECT_LINK_LIBS})
