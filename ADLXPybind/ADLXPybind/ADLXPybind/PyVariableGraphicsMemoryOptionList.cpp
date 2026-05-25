// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/ISystem3.h"

namespace py = pybind11;
using namespace adlx;

class PyVariableGraphicsMemoryOptionList : public IADLXVariableGraphicsMemoryOptionList
{
public:
    using IADLXVariableGraphicsMemoryOptionList::IADLXVariableGraphicsMemoryOptionList;

    adlx_uint Size() override {
        PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXVariableGraphicsMemoryOptionList, Size);
    }
    adlx_bool Empty() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXVariableGraphicsMemoryOptionList, Empty);
    }
    adlx_uint Begin() override {
        PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXVariableGraphicsMemoryOptionList, Begin);
    }
    adlx_uint End() override {
        PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXVariableGraphicsMemoryOptionList, End);
    }
    ADLX_RESULT At(const adlx_uint location, IADLXVariableGraphicsMemoryOption** ppItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemoryOptionList, At);
    }
    ADLX_RESULT Add_Back(IADLXVariableGraphicsMemoryOption* pItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVariableGraphicsMemoryOptionList, Add_Back);
    }
};
