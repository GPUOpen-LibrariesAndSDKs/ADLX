// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUAutoTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUAutoTuning : public IADLXGPUAutoTuning
{
public:
	using IADLXGPUAutoTuning::IADLXGPUAutoTuning;

	ADLX_RESULT IsCurrentOverclockGPU(adlx_bool* isOverclockGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, IsCurrentOverclockGPU);
	}

	ADLX_RESULT IsCurrentOverclockVRAM(adlx_bool* isOverclockVRAM) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, IsCurrentOverclockVRAM);
	}

	ADLX_RESULT IsCurrentUndervoltGPU(adlx_bool* isUndervoltGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, IsCurrentUndervoltGPU);
	}

	ADLX_RESULT IsSupportedOverclockGPU(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, IsSupportedOverclockGPU);
	}

	ADLX_RESULT IsSupportedOverclockVRAM(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, IsSupportedOverclockVRAM);
	}

	ADLX_RESULT IsSupportedUndervoltGPU(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, IsSupportedUndervoltGPU);
	}

	ADLX_RESULT StartOverclockGPU(IADLXGPUAutoTuningCompleteListener* pCompleteListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, StartOverclockGPU);
	}

	ADLX_RESULT StartOverclockVRAM(IADLXGPUAutoTuningCompleteListener* pCompleteListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, StartOverclockVRAM);
	}

	ADLX_RESULT StartUndervoltGPU(IADLXGPUAutoTuningCompleteListener* pCompleteListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAutoTuning, StartUndervoltGPU);
	}
};
