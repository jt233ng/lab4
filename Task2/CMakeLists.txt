cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(Task2 C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Task2
  main.c
)

pico_enable_stdio_uart(Task2 0)
pico_enable_stdio_usb(Task2 1)

pico_add_extra_outputs(Task2)

target_link_libraries(Task2 pico_stdlib)