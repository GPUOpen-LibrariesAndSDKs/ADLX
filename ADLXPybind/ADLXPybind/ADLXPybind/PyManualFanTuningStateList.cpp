// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualFanTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualFanTuningStateList : public IADLXManualFanTuningStateList
{
public:
	using IADLXManualFanTuningStateList::IADLXManualFanTuningStateList;

	ADLX_RESULT    Add_Back(IADLXManualFanTuningState* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuningStateList, Add_Back);
	}

	ADLX_RESULT    At(const adlx_uint location, IADLXManualFanTuningState** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuningStateList, At);
	}
};
