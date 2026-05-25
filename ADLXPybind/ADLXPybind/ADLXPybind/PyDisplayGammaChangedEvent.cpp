// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayGammaChangedEvent : public IADLXDisplayGammaChangedEvent
{
public:
	using IADLXDisplayGammaChangedEvent::IADLXDisplayGammaChangedEvent;

	ADLX_RESULT    GetDisplay(IADLXDisplay** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGammaChangedEvent, GetDisplay);
	}

	adlx_bool    IsDeGammaChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplayGammaChangedEvent, IsDeGammaChanged);
	}

	adlx_bool    IsGammaCoefficientChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplayGammaChangedEvent, IsGammaCoefficientChanged);
	}

	adlx_bool    IsGammaRampChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplayGammaChangedEvent, IsGammaRampChanged);
	}

	adlx_bool    IsReGammaChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplayGammaChangedEvent, IsReGammaChanged);
	}
	
	ADLX_SYNC_ORIGIN GetOrigin() override {
		PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLXDisplayGammaChangedEvent, GetOrigin);
	}
};
