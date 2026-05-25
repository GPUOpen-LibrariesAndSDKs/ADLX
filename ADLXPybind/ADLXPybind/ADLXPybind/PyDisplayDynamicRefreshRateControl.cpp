// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>

#include "../../../SDK/Include/IDisplaySettings.h"

namespace py = pybind11;
using namespace adlx;

class PyDisplayDynamicRefreshRateControl : public IADLXDisplayDynamicRefreshRateControl
{
public:
    using IADLXDisplayDynamicRefreshRateControl::IADLXDisplayDynamicRefreshRateControl;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayDynamicRefreshRateControl, IsSupported);
    }

    ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayDynamicRefreshRateControl, IsEnabled);
    }

    ADLX_RESULT SetEnabled(adlx_bool enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayDynamicRefreshRateControl, SetEnabled);
    }
};
