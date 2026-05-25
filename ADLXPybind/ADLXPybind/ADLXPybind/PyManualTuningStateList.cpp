// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualTuningStateList : public IADLXManualTuningStateList
{
public:
	using IADLXManualTuningStateList::IADLXManualTuningStateList;

	ADLX_RESULT    Add_Back(IADLXManualTuningState* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualTuningStateList, Add_Back);
	}

	ADLX_RESULT    At(const adlx_uint location, IADLXManualTuningState** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualTuningStateList, At);
	}
};
