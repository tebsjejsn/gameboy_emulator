cmake_minimum_required(VERSION 3.20)
project(gameboy CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL3 CONFIG REQUIRED)

add_executable(gameboy
    "Source Files/main.cpp"
    "Source Files/cartridge.cpp"
    "Header Files/cartridge.h"
)
target_include_directories(gameboy PRIVATE "Header Files")
target_link_libraries(gameboy PRIVATE SDL3::SDL3)