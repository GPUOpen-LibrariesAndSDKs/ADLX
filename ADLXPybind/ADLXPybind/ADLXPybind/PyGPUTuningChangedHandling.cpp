// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUTuningChangedHandling : public IADLXGPUTuningChangedHandling
{
public:
	using IADLXGPUTuningChangedHandling::IADLXGPUTuningChangedHandling;

	ADLX_RESULT AddGPUTuningEventListener(IADLXGPUTuningChangedListener* pGPUTuningChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningChangedHandling, AddGPUTuningEventListener);
	}

	ADLX_RESULT RemoveGPUTuningEventListener(IADLXGPUTuningChangedListener* pGPUTuningChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningChangedHandling, RemoveGPUTuningEventListener);
	}
};
