// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IMultiMedia.h"

namespace py = pybind11;
using namespace adlx;

class PyVideoSuperResolution : public IADLXVideoSuperResolution
{
public:
    using IADLXVideoSuperResolution::IADLXVideoSuperResolution;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoSuperResolution, IsSupported);
    }
    ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoSuperResolution, IsEnabled);
    }
    ADLX_RESULT SetEnabled(adlx_bool enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoSuperResolution, SetEnabled);
    }
};
