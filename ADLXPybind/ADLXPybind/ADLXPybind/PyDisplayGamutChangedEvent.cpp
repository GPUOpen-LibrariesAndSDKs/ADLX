// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayGamutChangedEvent : public IADLXDisplayGamutChangedEvent
{
public:
	using IADLXDisplayGamutChangedEvent::IADLXDisplayGamutChangedEvent;

	ADLX_RESULT    GetDisplay(IADLXDisplay** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamutChangedEvent, GetDisplay);
	}

	adlx_bool IsColorSpaceChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplayGamutChangedEvent, IsColorSpaceChanged);
	}

	adlx_bool IsWhitePointChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplayGamutChangedEvent, IsWhitePointChanged);
	}

	ADLX_SYNC_ORIGIN GetOrigin() override {
		PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLXDisplayGamutChangedEvent, GetOrigin);
	}
};
