cmake_minimum_required(VERSION 3.15...3.20)

project(Advanced_Programming_In_UNIX_Environment LANGUAGES C)


SET(CMAKE_C_STANDARD 99)
SET(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-Wall")

set(CMAKE_C_FLAGS_DEBUG "-ggdb")
set(CMAKE_C_FLAGS_RELEASE "-O3")  # full optimization

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(LIB_SOURCES
  apue_lib/src/error.c)
set(LIB_HEADERES
  apue_lib/inc/apue.h)

add_library(apue_library STATIC "${LIB_SOURCES}" "${LIB_HEADERES}")

target_include_directories(apue_library PUBLIC apue_lib/inc)

# target_compile_features(apue_library PUBLIC c_std_99)

add_subdirectory(introduction)
add_subdirectory(standardization_implementation)
add_subdirectory(file_IO)
add_subdirectory(files_and_directories)
add_subdirectory(standard_io_library)
add_subdirectory(system_data_files_and_information)
add_subdirectory(process_environment)
add_subdirectory(process_control)
add_subdirectory(signals)
add_subdirectory(threads)
