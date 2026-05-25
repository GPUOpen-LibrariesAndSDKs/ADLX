// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayChangeHandler : public IADLXDisplayChangedHandling
{
public:
	using IADLXDisplayChangedHandling::IADLXDisplayChangedHandling;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT AddDisplayListEventListener(IADLXDisplayListChangedListener* pDisplayListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayListEventListener);
	}

	ADLX_RESULT RemoveDisplayListEventListener(IADLXDisplayListChangedListener* pDisplayListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayListEventListener);
	}

	ADLX_RESULT AddDisplayGamutEventListener(IADLXDisplayGamutChangedListener* pDisplayGamutChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayGamutEventListener);
	}

	ADLX_RESULT RemoveDisplayGamutEventListener(IADLXDisplayGamutChangedListener* pDisplayGamutChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayGamutEventListener);
	}

	ADLX_RESULT AddDisplayGammaEventListener(IADLXDisplayGammaChangedListener* pDisplayGammaChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayGammaEventListener);
	}

	ADLX_RESULT RemoveDisplayGammaEventListener(IADLXDisplayGammaChangedListener* pDisplayGammaChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayGammaEventListener);
	}

	ADLX_RESULT AddDisplay3DLUTEventListener(IADLXDisplay3DLUTChangedListener* pDisplay3DLUTChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplay3DLUTEventListener);
	}

	ADLX_RESULT RemoveDisplay3DLUTEventListener(IADLXDisplay3DLUTChangedListener* pDisplay3DLUTChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplay3DLUTEventListener);
	}

	ADLX_RESULT AddDisplaySettingsEventListener(IADLXDisplaySettingsChangedListener* pDisplaySettingsChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplaySettingsEventListener);
	}

	ADLX_RESULT RemoveDisplaySettingsEventListener(IADLXDisplaySettingsChangedListener* pDisplaySettingsChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplaySettingsEventListener);
	}
};
