// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/ISystem2.h"

namespace py = pybind11;
using namespace adlx;

class PyGPU2List : public IADLXGPU2List
{
public:
    using IADLXGPU2List::IADLXGPU2List;

    ADLX_RESULT At(const adlx_uint location, IADLXGPU2** ppItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU2List, At);
    }

    ADLX_RESULT Add_Back(IADLXGPU2* pItem) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU2List, Add_Back);
    }
};
