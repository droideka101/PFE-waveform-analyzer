cmake_minimum_required(VERSION 4.0)
project(Project_file C)

set(CMAKE_C_STANDARD 99)

add_executable(Project_file src/main.c
        include/waveform.h
        src/waveform.c
        include/io.h
        src/io.c)

target_include_directories(Project_file PRIVATE include)