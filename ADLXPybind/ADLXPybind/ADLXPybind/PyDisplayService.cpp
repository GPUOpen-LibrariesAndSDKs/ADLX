// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays3.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayService : public IADLXDisplayServices3
{
public:
	using IADLXDisplayServices3::IADLXDisplayServices3;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT GetNumberOfDisplays(adlx_uint* numDisplays) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetNumberOfDisplays);
	}

	ADLX_RESULT GetDisplays(IADLXDisplayList** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetDisplays);
	}

	ADLX_RESULT Get3DLUT(IADLXDisplay* pDisplay, IADLXDisplay3DLUT** ppDisp3DLUT) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, Get3DLUT);
	}

	ADLX_RESULT GetGamut(IADLXDisplay* pDisplay, IADLXDisplayGamut** ppDispGamut) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetGamut);
	}

	ADLX_RESULT GetGamma(IADLXDisplay* pDisplay, IADLXDisplayGamma** ppDispGamma) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetGamma);
	}

	ADLX_RESULT GetDisplayChangedHandling(IADLXDisplayChangedHandling** ppDisplayChangeHandling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetDisplayChangedHandling);
	}

	ADLX_RESULT  GetFreeSync(IADLXDisplay* pDisplay, IADLXDisplayFreeSync** ppFreeSync) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetFreeSync);
	}

	ADLX_RESULT  GetVirtualSuperResolution(IADLXDisplay* pDisplay, IADLXDisplayVSR** ppVSR) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetVirtualSuperResolution);
	}

	ADLX_RESULT  GetGPUScaling(IADLXDisplay* pDisplay, IADLXDisplayGPUScaling** ppGPUScaling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetGPUScaling);
	}

	ADLX_RESULT  GetScalingMode(IADLXDisplay* pDisplay, IADLXDisplayScalingMode** ppScalingMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetScalingMode);
	}

	ADLX_RESULT  GetIntegerScaling(IADLXDisplay* pDisplay, IADLXDisplayIntegerScaling** ppIntegerScaling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetIntegerScaling);
	}

	ADLX_RESULT  GetColorDepth(IADLXDisplay* pDisplay, IADLXDisplayColorDepth** ppColorDepth) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetColorDepth);
	}

	ADLX_RESULT  GetPixelFormat(IADLXDisplay* pDisplay, IADLXDisplayPixelFormat** ppPixelFormat) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetPixelFormat);
	}

	ADLX_RESULT  GetCustomColor(IADLXDisplay* pDisplay, IADLXDisplayCustomColor** ppCustomColor) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetCustomColor);
	}

	ADLX_RESULT  GetHDCP(IADLXDisplay* pDisplay, IADLXDisplayHDCP** ppHDCP) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetHDCP);
	}

	ADLX_RESULT  GetCustomResolution(IADLXDisplay* pDisplay, IADLXDisplayCustomResolution** ppCustomResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetCustomResolution);
	}

	ADLX_RESULT  GetVariBright(IADLXDisplay* pDisplay, IADLXDisplayVariBright** ppVariBright) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetVariBright);
	}

    ADLX_RESULT GetDisplayBlanking(IADLXDisplay* pDisplay, IADLXDisplayBlanking** ppDisplayBlanking) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetDisplayBlanking);
    }

	// IADLXDisplayServices2
	ADLX_RESULT GetDisplayConnectivityExperience(IADLXDisplay* pDisplay, IADLXDisplayConnectivityExperience** ppDisplayConnectivityExperience) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetDisplayConnectivityExperience);
	}

	// IADLXDisplayServices3
	ADLX_RESULT GetDynamicRefreshRateControl(IADLXDisplay* pDisplay, IADLXDisplayDynamicRefreshRateControl** ppDRRC) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetDynamicRefreshRateControl);
	}
	ADLX_RESULT GetFreeSyncColorAccuracy(IADLXDisplay* pDisplay, IADLXDisplayFreeSyncColorAccuracy** ppFSCA) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices3, GetFreeSyncColorAccuracy);
	}
};
