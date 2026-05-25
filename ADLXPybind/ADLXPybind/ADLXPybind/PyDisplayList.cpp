// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayList : public IADLXDisplayList
{
public:
	using IADLXDisplayList::IADLXDisplayList;

	ADLX_RESULT Add_Back(IADLXDisplay* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXDisplay** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayList, At);
	}
};
