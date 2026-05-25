// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayResolution : public IADLXDisplayResolution
{
public:
	using IADLXDisplayResolution::IADLXDisplayResolution;

	ADLX_RESULT GetValue(ADLX_CustomResolution* customResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayResolution, GetValue);
	}

	ADLX_RESULT SetValue(ADLX_CustomResolution customResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayResolution, GetValue);
	}
};
