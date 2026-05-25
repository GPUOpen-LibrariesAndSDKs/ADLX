// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayResolutionList : public IADLXDisplayResolutionList
{
public:
	using IADLXDisplayResolutionList::IADLXDisplayResolutionList;

	ADLX_RESULT Add_Back(IADLXDisplayResolution* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayResolutionList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXDisplayResolution** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayResolutionList, At);
	}
};
