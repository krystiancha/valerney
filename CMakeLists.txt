cmake_minimum_required(VERSION 3.8)
project(valerney)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_C_STANDARD 11)

# change to your MCU
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=attiny85")

set(SOURCE_FILES main.c)
add_executable(valerney ${SOURCE_FILES})