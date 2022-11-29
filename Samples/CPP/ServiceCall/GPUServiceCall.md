<!--
# Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
-->
# Background

User may encounter a situation where they cannot directly use ADLX
functionalities in windows service application.

This documentation demonstrates how to call ADLX functionalities in
windows service call.

We have the sample codes in
"ADLX\\Samples\\CPP\\ServiceCall\\GPUService" as CPP project or
"ADLX\\Samples\\C\\ServiceCall\\GPUService" as C project. They both
generate executable "GPUService.exe".

# Usage

This executable is run as service (if you run it as a normal application
it will abort with errors)

## Install this service

1)  Open windows command line utility with administrator permission.
    Switch directory to the executable's path, take my dev PC for
    example:

> "D:\\DevShared3\\Work\\Repo\\drivers\\drivers\\ADLX\\Samples\\C\\build\\bin\\Debug\\"

2)  Copy "ADLX.dll"(ADLX library binary) in this folder, then enter
    "GPUService.exe -install:

> ![](media/image1.png)

3)  Check if the service is installed:

> Open windows' service settings by win+R with services.msc:
>
> ![Graphical user interface, text, application Description
> automatically generated](media/image2.png){width="3.075569772528434in"
> height="1.7870527121609798in"}
>
> Check service with name "ADLX GPU Service"
>
> ![](media/image3.png)

## Uninstall "ADLX GPU Service"

Open windows command line utility with administrator permission, enter
"GPUService.exe -remove"

![](media/image4.png)

The service is removed in OS.

## Debug this service

1.  Start the service:

![](media/image5.png)

2.  Run the debugging executable (compiled with debug configuration)

Open Dbgview.exe (visual studio contains it by default) with
administrator mode to view the output of this service. By default, the
service runs a worker thread in backgound to output GPU vendor id and
name periodically with 3 seconds.

3.  Set Dbgview.exe (admin mode) with below options:

![](media/image6.png)

4.  Check the service outputs (with "ADLX Call Service:" prefix):

![](media/image7.png)
