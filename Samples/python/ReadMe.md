@page page_sample_py Python

<!--
# Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
-->
This document describes how to build the Python bindings for ADLX, and the ADLX Python samples, as well as the environment in which they can be executed. The ADLX Python samples demonstrate how to program with ADLX in a Python application.

<h2>Supported Operating Systems</h2>
Windows® 10 (32- and 64-bit versions) and up.

<h2>Building the ADLXCSharpBind</h2>
These are the instructions for building the ADLX Python bindings for the ADLX Python samples.

<h2>Build Tool</h2>
Visual Studio 2019 with C and C++ components for desktop.

<h2>Prerequisites</h2>
- <b>ADLX SDK</b> is installed.
- <b>Python 3.9</b> is installed.
- <b>pybind11</b> is installed.
- The path to the Python 3.9 installation is set to the <b>PYHOME</b> system environment variable.

<b>Note:</b> The ADLX library is installed along with the AMD display driver.

<h2>Build Instructions</h2>
<ol>
    <li> Run Visual Studio 2019. </li>
    <li> Open `~ADLX\drivers\ADLX\Samples\python\ADLXPybind\ADLXPybind.sln`.</li>
    <li> Rebuild the project.</li>
</ol>

<h2>Building the ADLX Python samples</h2>
These are the instructions for building the <b>DisplayInfo</b> ADLX Python sample. 
Similar instructions must be followed for building the other ADLX Python samples.

<h2>Build Tool</h2>
Visual Studio Code

<h2>Prerequisites</h2>
- <b>ADLX SDK</b> is installed.
- <b>ADLXCSharpBind</b> is built.

<b>Note:</b> The ADLX library is installed along with the AMD display driver.

<h2>Build Instructions</h2>
<ol>
    <li> Run Visual Studio Code. </li>
    <li> Open `~ADLX\drivers\ADLX\Samples\python\DisplayInfo`. </li>
    <li> Rebuild the project.</li>
</ol>

