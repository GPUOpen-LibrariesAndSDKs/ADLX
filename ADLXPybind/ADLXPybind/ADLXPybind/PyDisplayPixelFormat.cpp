// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayPixelFormat : public IADLXDisplayPixelFormat
{
public:
	using IADLXDisplayPixelFormat::IADLXDisplayPixelFormat;

	ADLX_RESULT GetValue(ADLX_PIXEL_FORMAT* pixelFormat) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, GetValue);
	}
	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, IsSupported);
	}
	ADLX_RESULT IsSupportedPixelFormat(ADLX_PIXEL_FORMAT pixelFormat, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, IsSupportedPixelFormat);
	}
	ADLX_RESULT IsSupportedRGB444Full(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, IsSupportedRGB444Full);
	}
	ADLX_RESULT IsSupportedRGB444Limited(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, IsSupportedRGB444Limited);
	}
	ADLX_RESULT IsSupportedYCbCr420(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, IsSupportedYCbCr420);
	}
	ADLX_RESULT IsSupportedYCbCr422(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, IsSupportedYCbCr422);
	}
	ADLX_RESULT IsSupportedYCbCr444(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, IsSupportedYCbCr444);
	}
	ADLX_RESULT SetValue(ADLX_PIXEL_FORMAT pixelFormat) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayPixelFormat, SetValue);
	}
};
