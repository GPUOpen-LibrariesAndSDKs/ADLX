// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning1.h"

namespace py = pybind11;
using namespace adlx;

class PySmartShiftEco : public IADLXSmartShiftEco
{
public:
    using IADLXSmartShiftEco::IADLXSmartShiftEco;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftEco, IsSupported);
    }
    ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftEco, IsEnabled);
    }
    ADLX_RESULT SetEnabled(adlx_bool enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftEco, SetEnabled);
    }
    ADLX_RESULT IsInactive(adlx_bool* inactive) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftEco, IsInactive);
    }
    ADLX_RESULT GetInactiveReason(ADLX_SMARTSHIFT_ECO_INACTIVE_REASON* reason) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftEco, GetInactiveReason);
    }
};
