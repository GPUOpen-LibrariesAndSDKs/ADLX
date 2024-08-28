#
# Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.8)

set(project "DisplayInfo")

project(${project})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/../../build/bin/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE PATH "" FORCE)

set(all_file 
  "mainDisplayInfo.cpp"
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../SDK/platform/Windows/WinAPIs.cpp
 )
 
add_executable (${project} ${all_file})

