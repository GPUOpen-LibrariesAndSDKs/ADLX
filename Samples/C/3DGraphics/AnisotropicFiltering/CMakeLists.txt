#
# Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.8)

set(project "AnisotropicFiltering")

project(${project})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/../../build/bin/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../)

set(all_file 
  "mainAnisotropicFiltering.c"
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/ADLXHelper/Windows/C/ADLXHelper.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/ADLXHelper/Windows/C/ADLXHelper.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/platform/Windows/WinAPIs.c
 )
 
add_executable (${project} ${all_file})

