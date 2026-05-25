// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDesktops.h"


namespace py = pybind11;
using namespace adlx;


class PyDesktopList : public IADLXDesktopList
{
public:
	using IADLXDesktopList::IADLXDesktopList;

	ADLX_RESULT Add_Back(IADLXDesktop* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXDesktop** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopList, At);
	}
};
