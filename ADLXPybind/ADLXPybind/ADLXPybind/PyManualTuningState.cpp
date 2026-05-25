// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualTuningState : public IADLXManualTuningState
{
public:
	using IADLXManualTuningState::IADLXManualTuningState;

	ADLX_RESULT    GetFrequency(adlx_int* value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualTuningState, GetFrequency);
	}

	ADLX_RESULT    GetVoltage(adlx_int* value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualTuningState, GetVoltage);
	}

	ADLX_RESULT    SetFrequency(adlx_int value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualTuningState, SetFrequency);
	}

	ADLX_RESULT    SetVoltage(adlx_int value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualTuningState, SetVoltage);
	}


};
