#
# Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
set(project "SyncMultimedia")

set(all_file
  "mainSyncMultimedia.c"
  ${CMAKE_SOURCE_DIR}/../../SDK/ADLXHelper/Windows/C/ADLXHelper.h
  ${CMAKE_SOURCE_DIR}/../../SDK/ADLXHelper/Windows/C/ADLXHelper.c
  ${CMAKE_SOURCE_DIR}/../../SDK/platform/Windows/WinAPIs.c
 )

add_executable (${project} ${all_file})
