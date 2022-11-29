@page page_sample_java Java

<!--
# Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
-->
This document describes how to build the Java bindings for ADLX, and the ADLX Java samples, as well as the environment in which they can be executed. The ADLX Java samples demonstrate how to program with ADLX in a Java application.

<h2>Supported Operating Systems</h2>
Windows® 10 (32- and 64-bit versions) and up.

<h2>Building the ADLXCSharpBind</h2>
These are the instructions for building the ADLX Java bindings for the ADLX Java samples.

<h2>Build Tool</h2>
Visual Studio 2019 with C and C++ components for desktop.

<h2>Prerequisites</h2>
- <b>ADLX SDK</b> is installed.
- <b>Visual Studio 2019</b> is installed.
- <b>swigwin 4.0.2</b> is installed, and the path to the swigwin 4.0.2 installation is added to the <b>Path</b> user environment variable.
- <b>OpenJDK 17</b> is installed.
- The path to the OpenJDK 17 installation is added to the <b>JAVA_HOME</b> system environment variable.
- The bin path for the OpenJDK 17 installation is added to the <b>Path</b> system environment variable.

<h2>Build Instructions</h2>
<ol>
    <li> Run Visual Studio 2019.</li>
    <li> Open `~ADLX\drivers\ADLX\Samples\java\ADLXJavaBind\ADLXJavaBind.sln`.</li>
    <li> Rebuild the project</li>
</ol>

<h2>Building the ADLX Java samples</h2>
These are the instructions for building the <b>DisplayInfo</b> ADLX Java sample. 
Similar instructions must be followed for building the other ADLX Java samples.

<h2>Build Tool</h2>
Visual Studio Code

<h2>Prerequisites</h2>
- <b>ADLX SDK</b> is installed.
- <b>ADLXCSharpBind</b> is built.

<b>Note:</b> The ADLX library is installed along with the AMD display driver.

<h2>Build Instructions</h2>
<ol>
    <li> Run Visual Studio Code.</li>
    <li> Open `~ADLX\drivers\ADLX\Samples\java\DisplayInfo`.</li>
    <li> Rebuild the project</li>
</ol>
