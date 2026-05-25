// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IPowerTuning.h"

namespace py = pybind11;
using namespace adlx;

class PySmartShiftMax : public IADLXSmartShiftMax
{
public:
    using IADLXSmartShiftMax::IADLXSmartShiftMax;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftMax, IsSupported);
    }
    ADLX_RESULT GetBiasMode(ADLX_SSM_BIAS_MODE* mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftMax, GetBiasMode);
    }
    ADLX_RESULT SetBiasMode(ADLX_SSM_BIAS_MODE mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftMax, SetBiasMode);
    }
    ADLX_RESULT GetBiasRange(ADLX_IntRange* range) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftMax, GetBiasRange);
    }
    ADLX_RESULT GetBias(adlx_int* bias) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftMax, GetBias);
    }
    ADLX_RESULT SetBias(adlx_int bias) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSmartShiftMax, SetBias);
    }
};
