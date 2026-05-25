// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplay : public IADLXDisplay
{
public:
	using IADLXDisplay::IADLXDisplay;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT ManufacturerID(adlx_uint* manufacturerID) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ManufacturerID);
	}

	ADLX_RESULT DisplayType(ADLX_DISPLAY_TYPE* displayType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, DisplayType);
	}

	ADLX_RESULT ConnectorType(ADLX_DISPLAY_CONNECTOR_TYPE* connectType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ConnectorType);
	}

	ADLX_RESULT Name(const char** displayName) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, Name);
	}

	ADLX_RESULT EDID(const char** edid) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, EDID);
	}

	ADLX_RESULT NativeResolution(adlx_int* maxHResolution, adlx_int* maxVResolution) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, NativeResolution);
	}

	ADLX_RESULT RefreshRate(adlx_double* refreshRate) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, RefreshRate);
	}

	ADLX_RESULT PixelClock(adlx_uint* pixelClock) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, PixelClock);
	}

	ADLX_RESULT ScanType(ADLX_DISPLAY_SCAN_TYPE* scanType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ScanType);
	}

	ADLX_RESULT GetGPU(IADLXGPU** ppGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, GetGPU);
	}

	ADLX_RESULT UniqueId(adlx_size* uniqueId) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, UniqueId);
	}
};
