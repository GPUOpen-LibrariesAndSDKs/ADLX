// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyMemoryTimingDescriptionList : public IADLXMemoryTimingDescriptionList
{
public:
	using IADLXMemoryTimingDescriptionList::IADLXMemoryTimingDescriptionList;

	ADLX_RESULT    Add_Back(IADLXMemoryTimingDescription* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMemoryTimingDescriptionList, Add_Back);
	}

	ADLX_RESULT    At(const adlx_uint location, IADLXMemoryTimingDescription** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMemoryTimingDescriptionList, At);
	}
};
