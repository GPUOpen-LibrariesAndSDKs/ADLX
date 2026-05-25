// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning.h"

namespace py = pybind11;
using namespace adlx;

class PyPowerTuningChangedHandling : public IADLXPowerTuningChangedHandling
{
public:
    using IADLXPowerTuningChangedHandling::IADLXPowerTuningChangedHandling;

    ADLX_RESULT AddPowerTuningEventListener(IADLXPowerTuningChangedListener* pPowerTuningChangedListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPowerTuningChangedHandling, AddPowerTuningEventListener);
    }
    ADLX_RESULT RemovePowerTuningEventListener(IADLXPowerTuningChangedListener* pPowerTuningChangedListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPowerTuningChangedHandling, RemovePowerTuningEventListener);
    }
};
