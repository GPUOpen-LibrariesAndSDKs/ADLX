// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IMultiMedia.h"

namespace py = pybind11;
using namespace adlx;

class PyVideoUpscale : public IADLXVideoUpscale
{
public:
    using IADLXVideoUpscale::IADLXVideoUpscale;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoUpscale, IsSupported);
    }
    ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoUpscale, IsEnabled);
    }
    ADLX_RESULT GetSharpnessRange(ADLX_IntRange* range) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoUpscale, GetSharpnessRange);
    }
    ADLX_RESULT GetSharpness(adlx_int* sharpness) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoUpscale, GetSharpness);
    }
    ADLX_RESULT SetEnabled(adlx_bool enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoUpscale, SetEnabled);
    }
    ADLX_RESULT SetSharpness(adlx_int sharpness) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXVideoUpscale, SetSharpness);
    }
};
