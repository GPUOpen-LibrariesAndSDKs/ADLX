// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/ISystem3.h"

namespace py = pybind11;
using namespace adlx;

class PyVariableGraphicsMemory : public IADLXVariableGraphicsMemory
{
public:
    using IADLXVariableGraphicsMemory::IADLXVariableGraphicsMemory;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemory, IsSupported);
    }
    ADLX_RESULT GetDefaultOption(IADLXVariableGraphicsMemoryOption** ppOption) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemory, GetDefaultOption);
    }
    ADLX_RESULT GetOption(IADLXVariableGraphicsMemoryOption** ppOption) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemory, GetOption);
    }
    ADLX_RESULT GetAvailableOptions(IADLXVariableGraphicsMemoryOptionList** ppOptions) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemory, GetAvailableOptions);
    }
    ADLX_RESULT SetOption(IADLXVariableGraphicsMemoryOption* pOption) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemory, SetOption);
    }
};
