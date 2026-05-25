// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/ISmartAccessMemory.h"

namespace py = pybind11;
using namespace adlx;

class PySmartAccessMemory : public IADLXSmartAccessMemory
{
public:
    using IADLXSmartAccessMemory::IADLXSmartAccessMemory;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartAccessMemory, IsSupported);
    }
    ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartAccessMemory, IsEnabled);
    }
    ADLX_RESULT SetEnabled(adlx_bool enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartAccessMemory, SetEnabled);
    }
};
