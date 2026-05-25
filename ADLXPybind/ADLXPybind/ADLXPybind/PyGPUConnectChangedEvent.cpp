// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning1.h"

namespace py = pybind11;
using namespace adlx;

class PyGPUConnectChangedEvent : public IADLXGPUConnectChangedEvent
{
public:
    using IADLXGPUConnectChangedEvent::IADLXGPUConnectChangedEvent;

    ADLX_RESULT GetGPU(IADLXGPU2** ppGPU) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUConnectChangedEvent, GetGPU);
    }
    adlx_bool IsGPUAppsListChanged() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUConnectChangedEvent, IsGPUAppsListChanged);
    }
    adlx_bool IsGPUPowerChanged() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUConnectChangedEvent, IsGPUPowerChanged);
    }
    adlx_bool IsGPUPowerChangeError(ADLX_RESULT* pPowerChangeError) override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUConnectChangedEvent, IsGPUPowerChangeError);
    }
};
