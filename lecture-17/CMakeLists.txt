cmake_minimum_required(VERSION 3.15)

project(banksim)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra)

add_executable(banksim banksim.c)
