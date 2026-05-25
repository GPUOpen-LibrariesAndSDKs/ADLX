// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>

#include "../../../SDK/Include/IDisplaySettings.h"

namespace py = pybind11;
using namespace adlx;

class PyDisplayFreeSyncColorAccuracy : public IADLXDisplayFreeSyncColorAccuracy
{
public:
    using IADLXDisplayFreeSyncColorAccuracy::IADLXDisplayFreeSyncColorAccuracy;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayFreeSyncColorAccuracy, IsSupported);
    }

    ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayFreeSyncColorAccuracy, IsEnabled);
    }

    ADLX_RESULT SetEnabled(adlx_bool enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayFreeSyncColorAccuracy, SetEnabled);
    }
};
