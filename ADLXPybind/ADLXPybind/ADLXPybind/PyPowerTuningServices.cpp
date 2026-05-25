// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning1.h"

namespace py = pybind11;
using namespace adlx;

class PyPowerTuningServices : public IADLXPowerTuningServices1
{
public:
    using IADLXPowerTuningServices1::IADLXPowerTuningServices1;

    // IADLXPowerTuningServices
    ADLX_RESULT GetPowerTuningChangedHandling(IADLXPowerTuningChangedHandling** ppPowerTuningChangedHandling) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPowerTuningServices1, GetPowerTuningChangedHandling);
    }
    ADLX_RESULT GetSmartShiftMax(IADLXSmartShiftMax** ppSmartShiftMax) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPowerTuningServices1, GetSmartShiftMax);
    }
    // IADLXPowerTuningServices1
    ADLX_RESULT GetSmartShiftEco(IADLXSmartShiftEco** ppSmartShiftEco) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPowerTuningServices1, GetSmartShiftEco);
    }
    ADLX_RESULT IsGPUConnectSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPowerTuningServices1, IsGPUConnectSupported);
    }
    ADLX_RESULT GetGPUConnectGPUs(IADLXGPU2List** ppGPUs) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPowerTuningServices1, GetGPUConnectGPUs);
    }
};
