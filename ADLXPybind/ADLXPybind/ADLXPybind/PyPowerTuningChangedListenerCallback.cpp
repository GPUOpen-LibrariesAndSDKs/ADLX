// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning.h"
#include <functional>

namespace py = pybind11;
using namespace adlx;

class PyPowerTuningChangedListenerCallback : public IADLXPowerTuningChangedListener
{
public:
    std::function<bool(IADLXPowerTuningChangedEventPtr)> m_call;

    adlx_bool ADLX_STD_CALL OnPowerTuningChanged(IADLXPowerTuningChangedEvent* pPowerTuningChangedEvent) override
    {
        if (pPowerTuningChangedEvent == nullptr) return false;
        if (m_call) return m_call(pPowerTuningChangedEvent);
        return true;
    }
};
