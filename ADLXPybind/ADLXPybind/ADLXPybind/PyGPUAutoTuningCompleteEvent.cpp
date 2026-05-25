// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUAutoTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUAutoTuningCompleteEvent : public IADLXGPUAutoTuningCompleteEvent
{
public:
	using IADLXGPUAutoTuningCompleteEvent::IADLXGPUAutoTuningCompleteEvent;

	adlx_bool IsOverclockGPUCompleted() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUAutoTuningCompleteEvent, IsOverclockGPUCompleted);
	}

	adlx_bool IsOverclockVRAMCompleted() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUAutoTuningCompleteEvent, IsOverclockVRAMCompleted);
	}

	adlx_bool IsUndervoltGPUCompleted() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUAutoTuningCompleteEvent, IsUndervoltGPUCompleted);
	}

};
