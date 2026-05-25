// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings3.h"


namespace py = pybind11;
using namespace adlx;


class Py3DAMDFluidMotionFrames : IADLX3DAMDFluidMotionFrames1
{
public:
	using IADLX3DAMDFluidMotionFrames1::IADLX3DAMDFluidMotionFrames1;

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, SetEnabled);
	}

    ADLX_RESULT IsSupportedAlgorithm(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, IsSupportedAlgorithm);
    }

    ADLX_RESULT  GetAlgorithm(ADLX_AFMF_ALGORITHM* algorithm) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, GetAlgorithm);
    }

    ADLX_RESULT  SetAlgorithm(ADLX_AFMF_ALGORITHM algorithm) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, SetAlgorithm);
    }

    ADLX_RESULT  GetSearchMode(ADLX_AFMF_SEARCH_MODE_TYPE* mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, GetSearchMode);
    }

    ADLX_RESULT  SetSearchMode(ADLX_AFMF_SEARCH_MODE_TYPE mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, SetSearchMode);
    }

    ADLX_RESULT  GetPerformanceMode(ADLX_AFMF_PERFORMANCE_MODE_TYPE* mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, GetPerformanceMode);
    }
    ADLX_RESULT  SetPerformanceMode(ADLX_AFMF_PERFORMANCE_MODE_TYPE mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, SetPerformanceMode);
    }

    ADLX_RESULT  GetFastMotionResponse(ADLX_AFMF_FAST_MOTION_RESP* response) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, GetFastMotionResponse);
    }
    ADLX_RESULT  SetFastMotionResponse(ADLX_AFMF_FAST_MOTION_RESP response) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames1, SetFastMotionResponse);
    }
};
