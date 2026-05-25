// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/ISystem3.h"
#include <functional>

namespace py = pybind11;
using namespace adlx;

class PyGPUStressTestFinishedListenerCallback : public IADLXGPUStressTestFinishedListener
{
public:
    std::function<bool(IADLXGPU*, adlx_bool)> m_call;

    adlx_bool ADLX_STD_CALL OnGPUStressTestFinished(IADLXGPU3* pGPU, adlx_bool result) override
    {
        if (pGPU == nullptr) return false;
        if (m_call) return m_call(static_cast<IADLXGPU*>(pGPU), result);
        return true;
    }
};
