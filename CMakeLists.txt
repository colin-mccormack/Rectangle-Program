cmake_minimum_required(VERSION 3.20)
project(AO4_RECTANGLE_PROGRAM C)

set(CMAKE_C_STANDARD 99)

add_executable(AO4_RECTANGLE_PROGRAM main.c Lib/LinkedHashMap/LinkedHashMap.h Lib/LinkedHashMap/LinkedHashMap.c Lib/IO/FileWriter.h Lib/IO/FileWriter.c Lib/IO/IO.h Lib/IO/IO.c Configurations.h Lib/Operations/Operations.h Lib/Operations/Operations.c Lib/Rectangle/Rectangle.h Lib/Rectangle/Rectangle.c)

