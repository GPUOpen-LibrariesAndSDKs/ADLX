// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IApplications.h"
#include <functional>

namespace py = pybind11;
using namespace adlx;

class PyGPUAppsListEventListenerCallback : public IADLXGPUAppsListEventListener
{
public:
    std::function<bool(IADLXGPU2*, IADLXApplicationList*)> m_call;

    adlx_bool ADLX_STD_CALL OnGPUAppsListChanged(IADLXGPU2* pGPU, IADLXApplicationList* pApplications) override
    {
        if (pGPU == nullptr || pApplications == nullptr) return false;
        if (m_call) return m_call(pGPU, pApplications);
        return true;
    }
};
