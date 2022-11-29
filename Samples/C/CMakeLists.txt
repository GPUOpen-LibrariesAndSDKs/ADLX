#
# Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Samples")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/build/bin/)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} CACHE PATH "" FORCE)

file(COPY ${CMAKE_SOURCE_DIR}/../output-night-light.txt DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include_directories(../../)

#macro to get subdir list. the deep is 2
#[out] subdirnamelist
#[in] targetdir
macro(SUBDIRNAMELIST_MACRO subdirnamelist targetdir)
    # message(STATUS "macro subdirnamelist = ${subdirnamelist}")
    # message(STATUS "macro targetdir = ${targetdir}")
    file(GLOB children ${targetdir}/*/*) #deep is 2
    # message(STATUS "macro children = ${children}")
    set(dirlist "")
    foreach(child ${children})
        file(RELATIVE_PATH child_name ${targetdir} ${child})
        # message(STATUS "macro child = ${child_name}")
        # message(STATUS "targetdir/child = ${targetdir}/${child_name}")
        if(IS_DIRECTORY ${targetdir}/${child_name})
            # message(STATUS "yes dir : targetdir/child = ${targetdir}/${child_name}")
            list(APPEND dirlist ${child_name})
        endif()
    endforeach()
    list(APPEND ${subdirnamelist} ${dirlist})
    # message(STATUS "macro dirlist = ${dirlist}")
    # message(STATUS "macro subdirnamelist = ${subdirnamelist}")
endmacro()
 
#macro to check CMakeLists
#[out] hascmakelist
#[in] targetdir
macro(CHECK_DIR_HAS_CMAKELIST hascmakelist targetdir)
    # message(STATUS "macro check has cmakelist targetdir = ${targetdir}")
    set(${hascmakelist} FALSE)
    if(IS_DIRECTORY ${targetdir})
        # message(STATUS "macro check has cmakelist is dir, targetdir = ${targetdir}")
        if(EXISTS ${targetdir}/CMakeLists.txt)
            set(${hascmakelist} TRUE)
        endif()
    else()
        message(FATAL_ERROR "Invalid dir para: targetdir = ${targetdir}")
    endif()
endmacro()

#macro to add sub project
macro(AUTO_ADD_SUBDIRECTORY)
    set(subdirnamelisttemp "")
    SUBDIRNAMELIST_MACRO(subdirnamelisttemp ${CMAKE_CURRENT_SOURCE_DIR})
    # message(STATUS "macro add_subdir subdirnamelisttemp = ${subdirnamelisttemp}")
    foreach(subdir ${subdirnamelisttemp})
        # message(STATUS "macro add_subdir subdir = ${subdir}")
        set(hascmakelisttemp FALSE)
        CHECK_DIR_HAS_CMAKELIST(hascmakelisttemp ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        # message(STATUS "macro add_subdir hascmakelisttemp = ${hascmakelisttemp}")
        if(${hascmakelisttemp})
            message(STATUS "macro add_subdir go to add_subdir = ${subdir}")
            add_subdirectory(${subdir})
        endif()
    endforeach()
endmacro()

#Automatically traverse subdirectories, add sub project
AUTO_ADD_SUBDIRECTORY()