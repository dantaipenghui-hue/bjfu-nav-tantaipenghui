cmake_minimum_required(VERSION 3.10)
project(task2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 默认使用 Debug 构建，带调试符号，VS Code 断点调试才有效
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 1) Hello World
add_executable(hello_world
    src/hello_world/main.cpp
)

# 2) swap 
add_executable(swap
    src/swap/main.cpp
    src/swap.cpp
)

# 3) 成绩统计
add_executable(score_stats
    src/score_stats/main.cpp
    src/score_stats.cpp
)
