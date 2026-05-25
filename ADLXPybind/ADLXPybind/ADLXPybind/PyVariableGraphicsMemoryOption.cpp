// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/ISystem3.h"

namespace py = pybind11;
using namespace adlx;

class PyVariableGraphicsMemoryOption : public IADLXVariableGraphicsMemoryOption
{
public:
    using IADLXVariableGraphicsMemoryOption::IADLXVariableGraphicsMemoryOption;

    ADLX_RESULT Name(const char** name) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemoryOption, Name);
    }
    ADLX_RESULT Mode(ADLX_VARIABLE_GRAPHICS_MEMORY_MODE* mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemoryOption, Mode);
    }
    ADLX_RESULT MemoryCarved(adlx_double* memoryCarvedGb) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemoryOption, MemoryCarved);
    }
    ADLX_RESULT MemoryRemaining(adlx_double* memoryRemainingGb) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemoryOption, MemoryRemaining);
    }
};
