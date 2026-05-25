// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUPresetTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUPresetTuning : public IADLXGPUPresetTuning
{
public:
	using IADLXGPUPresetTuning::IADLXGPUPresetTuning;

	ADLX_RESULT IsCurrentBalanced(adlx_bool* isBalanced) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsCurrentBalanced);
	}

	ADLX_RESULT    IsCurrentPowerSaver(adlx_bool* isPowerSaver) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsCurrentPowerSaver);
	}

	ADLX_RESULT    IsCurrentQuiet(adlx_bool* isQuiet) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsCurrentQuiet);
	}

	ADLX_RESULT    IsCurrentRage(adlx_bool* isRage) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsCurrentRage);
	}

	ADLX_RESULT    IsCurrentTurbo(adlx_bool* isTurbo) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsCurrentTurbo);
	}

	ADLX_RESULT    IsSupportedBalanced(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsSupportedBalanced);
	}

	ADLX_RESULT    IsSupportedPowerSaver(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsSupportedPowerSaver);
	}

	ADLX_RESULT    IsSupportedQuiet(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsSupportedQuiet);
	}

	ADLX_RESULT    IsSupportedRage(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsSupportedRage);
	}

	ADLX_RESULT    IsSupportedTurbo(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, IsSupportedTurbo);
	}

	ADLX_RESULT    SetBalanced() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, SetBalanced);
	}

	ADLX_RESULT    SetPowerSaver() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, SetPowerSaver);
	}

	ADLX_RESULT    SetQuiet() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, SetQuiet);
	}

	ADLX_RESULT    SetRage() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, SetRage);
	}

	ADLX_RESULT    SetTurbo() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUPresetTuning, SetTurbo);
	}
};
