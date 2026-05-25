// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayCustomResolution : public IADLXDisplayCustomResolution
{
public:
	using IADLXDisplayCustomResolution::IADLXDisplayCustomResolution;

	ADLX_RESULT CreateNewResolution(IADLXDisplayResolution* pResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomResolution, CreateNewResolution);
	}
	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomResolution, IsSupported);
	}
	ADLX_RESULT GetCurrentAppliedResolution (IADLXDisplayResolution** ppResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomResolution, GetCurrentAppliedResolution);
	}
	ADLX_RESULT ADLX_STD_CALL GetResolutionList (IADLXDisplayResolutionList** ppResolutionList) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomResolution, GetResolutionList);
	}
	ADLX_RESULT DeleteResolution (IADLXDisplayResolution* pResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomResolution, DeleteResolution);
	}
};
