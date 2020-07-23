cmake_minimum_required(VERSION 3.0)
project(LI2 C)

set(CMAKE_C_STANDARD 11)

add_executable(balance src/main.c src/balance.c src/files.c src/interface.c)
