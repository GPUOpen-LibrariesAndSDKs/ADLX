//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#ifndef Custom_STRUCTURES_H
#define Custom_STRUCTURES_H
#pragma once

#include "../../../SDK/Include/ADLXDefines.h"


#pragma region PyADLIdsFromADLX
typedef struct
{
    adlx_int adapterIndex;
    adlx_int VidPnSourceId;
    adlx_int bus;
    adlx_int device;
    adlx_int function;
} PyADLIdsFromADLX;
#pragma endregion PyADLIdsFromADLX


#pragma region PyBdfFromADLXGPU
typedef struct
{
    adlx_int bus;
    adlx_int device;
    adlx_int function;
} PyBdfFromADLXGPU;
#pragma endregion PyBdfFromADLXGPU


#endif //Custom_STRUCTURES_H
