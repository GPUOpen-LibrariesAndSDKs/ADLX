// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning1.h"
#include <functional>

namespace py = pybind11;
using namespace adlx;

class PyGPUConnectChangedListenerCallback : public IADLXGPUConnectChangedListener
{
public:
    std::function<bool(IADLXGPUConnectChangedEventPtr)> m_call;

    adlx_bool ADLX_STD_CALL OnGPUConnectChanged(IADLXGPUConnectChangedEvent* pGPUConnectChangedEvent) override
    {
        if (pGPUConnectChangedEvent == nullptr) return false;
        if (m_call) return m_call(pGPUConnectChangedEvent);
        return true;
    }
};
