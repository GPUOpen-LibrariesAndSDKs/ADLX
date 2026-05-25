// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualFanTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualFanTuningState : public IADLXManualFanTuningState
{
public:
	using IADLXManualFanTuningState::IADLXManualFanTuningState;

	ADLX_RESULT GetFanSpeed(adlx_int* value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuningState, GetFanSpeed);
	}

	ADLX_RESULT GetTemperature(adlx_int* value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuningState, GetTemperature);
	}

	ADLX_RESULT SetFanSpeed(adlx_int value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuningState, SetFanSpeed);
	}

	ADLX_RESULT SetTemperature(adlx_int value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuningState, SetTemperature);
	}
};
