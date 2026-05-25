// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IApplications.h"


namespace py = pybind11;
using namespace adlx;


class PyApplicationList : public IADLXApplicationList
{
public:
	using IADLXApplicationList::IADLXApplicationList;

	ADLX_RESULT Add_Back(IADLXApplication* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXApplicationList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXApplication** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXApplicationList, At);
	}
};
