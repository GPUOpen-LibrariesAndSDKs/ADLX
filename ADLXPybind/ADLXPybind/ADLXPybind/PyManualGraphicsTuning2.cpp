// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualGFXTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualGraphicsTuning2 : public IADLXManualGraphicsTuning2_1
{
public:
	using IADLXManualGraphicsTuning2_1::IADLXManualGraphicsTuning2_1;

	ADLX_RESULT    GetGPUMaxFrequency(adlx_int* maxFreq) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUMaxFrequency);
	}

	ADLX_RESULT    GetGPUMaxFrequencyRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUMaxFrequencyRange);
	}

	ADLX_RESULT    GetGPUMinFrequency(adlx_int* minFreq) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUMinFrequency);
	}

	ADLX_RESULT    GetGPUMinFrequencyRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUMinFrequencyRange);
	}

	ADLX_RESULT    GetGPUVoltage(adlx_int* volt) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUVoltage);
	}

	ADLX_RESULT    GetGPUVoltageRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUVoltageRange);
	}

	ADLX_RESULT    SetGPUMaxFrequency(adlx_int maxFreq) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, SetGPUMaxFrequency);
	}

	ADLX_RESULT    SetGPUMinFrequency(adlx_int minFreq) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, SetGPUMinFrequency);
	}

	ADLX_RESULT    SetGPUVoltage(adlx_int volt) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, SetGPUVoltage);
	}

	ADLX_RESULT    GetGPUMinFrequencyDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUMinFrequencyDefault);
	}

	ADLX_RESULT    GetGPUMaxFrequencyDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUMaxFrequencyDefault);
	}

	ADLX_RESULT    GetGPUVoltageDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning2_1, GetGPUVoltageDefault);
	}

    
};
