cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(Task1_c C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Task1_c
  main.c
)

pico_enable_stdio_uart(Task1_c 0)
pico_enable_stdio_usb(Task1_c 1)

pico_add_extra_outputs(Task1_c)

target_link_libraries(Task1_c pico_stdlib)