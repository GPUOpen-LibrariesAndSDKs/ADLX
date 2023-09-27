@page page_sample_cs C# Samples
<!--
# Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
-->
This document describes how to build the C# bindings for ADLX, and the ADLX C# samples, as well as the environment in which they can be executed. The ADLX C# samples demonstrate how to program with ADLX in a C# application.

<h2>Supported Operating Systems</h2>
Windows® 10 (32- and 64-bit versions) and up.

<h2>Build Tool</h2>
Visual Studio 2019 with C and C++ components for desktop, and with C# components for desktop.

<h2>Prerequisites</h2>
- <b>ADLX SDK</b> is installed.
- <b>swigwin 4.0.2</b> is installed, and the path to the swigwin 4.0.2 installation is added to the <b>Path</b> user environment variable.

<b>Note:</b> The ADLX library is installed along with the AMD display driver.

<h2>Build Instructions</h2>
<ol>
    <li> Open `~ADLX\drivers\ADLX\Samples\csharp\sample.sln` with Visual Studio 2019.</li>
    <li> Select the build configuration, for example, <b>Release</b>, and <b>x64</b>.</li>
    <li> Set the sample as startup project. </li>
    <li> Rebuild the project. \n</li>
    <b>Note:</b> This procedure also builds the `ADLXCSharpBind` project in Visual Studio, which is required for any ALDX C# sample .
    <li> Run the sample from the path `~ADLX\Samples\csharp` for the corresponding build configuration and sample, for example `~ADLX\Samples\csharp\x64\Release\DisplayInfo.exe`.</li>
</ol>