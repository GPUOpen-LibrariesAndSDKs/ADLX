#
# Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.8)
set(KERNEL_MODE_DRIVER 0)
include(../../../../../../../gfx_cmake/cmake/AMDToolchainSetup.cmake)

project(GPUServiceDirect LANGUAGES CXX)

include(../../../../../../../gfx_cmake/cmake/AMDCMake.cmake)
include(CMakePackageConfigHelpers)

get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../out$<$<BOOL:${is_multi_config}>:/$<CONFIG>>)

add_executable(GPUServiceDirect)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../../)

 target_sources(GPUServiceDirect
  PRIVATE
  "../mainGPUServiceDirect.cpp"
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../SDK/platform/Windows/WinAPIs.cpp
  )
 
 target_include_directories(GPUServiceDirect
     PRIVATE
     ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../
  )

# Link libraries
target_link_libraries(GPUServiceDirect PRIVATE Advapi32)

#Set ouput path
set(build_artifact_out_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(MANIFEST_PATH ${CMAKE_CURRENT_BINARY_DIR}/temp.manifest)

# Use file(GENERATE) to create manifest at generation time (fixes parallel build race condition)
set(MANIFEST_CONTENT "<?xml version=\"1.0\" encoding=\"utf-8\" ?>
<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">
  <assemblyIdentity version=\"1.0.0.0\"
      processorArchitecture=\"amd64\"
      name=\"GPUServiceDirect.exe\"
      type=\"win32\" />
  <description>AMD External Event Utility</description>
  <trustInfo xmlns=\"urn:schemas-microsoft-com:asm.v2\">
    <security>
      <requestedPrivileges>
        <requestedExecutionLevel level=\"asInvoker\" uiAccess=\"false\"/>
      </requestedPrivileges>
    </security>
  </trustInfo>
</assembly>
")

file(GENERATE OUTPUT "${MANIFEST_PATH}" CONTENT "${MANIFEST_CONTENT}")

# Ensure manifest dependency (fixes parallel build race condition)
add_custom_target(GPUServiceDirect_manifest DEPENDS "${MANIFEST_PATH}")
add_dependencies(GPUServiceDirect GPUServiceDirect_manifest)

add_custom_command(TARGET GPUServiceDirect POST_BUILD
    COMMAND "${CMAKE_MT}"
            -manifest "${MANIFEST_PATH}"
            -outputresource:"${build_artifact_out_dir}/GPUServiceDirect.exe\;1"
    COMMENT "Embedding Windows manifest"
)

# Set up variables required by the amd_post_build_install() function
set(INST_DIR "ADLXUnitTest/Samples/ServiceCall")
amd_post_build_install(GPUServiceDirect)
