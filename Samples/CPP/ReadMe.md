@page page_sample_cpp C++ Samples
<!--
# Copyright (c) 2023 - 2024 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
-->
This document describes how to build the ADLX C++ samples and the environment in which they can be executed. The ADLX C++ samples are organized per domain, and they demonstrate the entire ADLX functionality.

<h2>Supported Operating Systems</h2>
Windows® 10 (32- and 64-bit versions) and up.

<h2>Build Tool</h2>
Visual Studio 2019 with C and C++ components for desktop.

<h2>Prerequisites</h2>
- <b>ADLX SDK</b> is installed.

<b>Note:</b> The ADLX library is installed along with the AMD display driver.

<h2>Build Instructions</h2>
<ol>
    <li> Run Visual Studio 2019.</li>
    <li> Click <b>File > Open > CMake</b>.</li>
    <li> Select the `~Samples\CPP` folder from the Address bar in the pop-up dialog box.</li>
    <li> Select `CMakeLists.txt` in `~ADLX\Samples\CPP` and click <b>Open</b>.</li>
    <li> Select <b>vs2019_Release_x64</b> in the Configuration drop-down.</li>
    <li> Click <b>Switch between available views > CMake Targets view</b> in the Solution Explorer.</li>
    <li> Click <b>Samples Project</b> and expand the list of samples. Right-click on the required sample and click <b>Set As Startup Item</b>. For example, `DisplayInfo.exe`.</li>
    <li> Right-click on the same sample and click <b>Build</b>.</li>
    <li> Run the sample.</li>
</ol>