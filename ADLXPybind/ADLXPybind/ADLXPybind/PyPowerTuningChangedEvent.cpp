// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning1.h"

namespace py = pybind11;
using namespace adlx;

class PyPowerTuningChangedEvent : public IADLXPowerTuningChangedEvent1
{
public:
    using IADLXPowerTuningChangedEvent1::IADLXPowerTuningChangedEvent1;

    ADLX_SYNC_ORIGIN GetOrigin() override {
        PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLXPowerTuningChangedEvent1, GetOrigin);
    }
    // IADLXPowerTuningChangedEvent
    adlx_bool IsSmartShiftMaxChanged() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXPowerTuningChangedEvent1, IsSmartShiftMaxChanged);
    }
    // IADLXPowerTuningChangedEvent1
    adlx_bool IsSmartShiftEcoChanged() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXPowerTuningChangedEvent1, IsSmartShiftEcoChanged);
    }
};
