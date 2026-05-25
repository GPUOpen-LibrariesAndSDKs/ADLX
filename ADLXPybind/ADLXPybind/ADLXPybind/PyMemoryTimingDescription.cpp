// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyMemoryTimingDescription : public IADLXMemoryTimingDescription
{
public:
	using IADLXMemoryTimingDescription::IADLXMemoryTimingDescription;

	ADLX_RESULT    GetDescription(ADLX_MEMORYTIMING_DESCRIPTION* description) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMemoryTimingDescription, GetDescription);
	}

};
