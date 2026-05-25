// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/ADLXDefines.h"


namespace py = pybind11;
using namespace adlx;


class PyInterface : public IADLXInterface
{
public:
	using IADLXInterface::IADLXInterface;

	adlx_long Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	ADLX_RESULT QueryInterface(const wchar_t* interfaceId, void** ppInterface) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	adlx_long Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}
};
