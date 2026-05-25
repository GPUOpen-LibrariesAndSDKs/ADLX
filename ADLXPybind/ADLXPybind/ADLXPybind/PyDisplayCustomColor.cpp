// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayCustomColor : public IADLXDisplayCustomColor
{
public:
	using IADLXDisplayCustomColor::IADLXDisplayCustomColor;

	ADLX_RESULT GetBrightness(adlx_int* currentBrightness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetValue);
	}
	ADLX_RESULT GetBrightnessRange (ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetBrightnessRange);
	}
	ADLX_RESULT GetContrast (adlx_int* currentContrast) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetContrast);
	}
	ADLX_RESULT GetContrastRange (ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetContrastRange);
	}
	ADLX_RESULT GetHue (adlx_int* currentHue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetHue);
	}
	ADLX_RESULT GetHueRange (ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetHueRange);
	}
	ADLX_RESULT GetSaturation (adlx_int* currentSaturation) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetSaturation);
	}
	ADLX_RESULT GetSaturationRange (ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetSaturationRange);
	}
	ADLX_RESULT GetTemperature (adlx_int* currentTemperature) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetTemperature);
	}
	ADLX_RESULT GetTemperatureRange (ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, GetTemperatureRange);
	}
	ADLX_RESULT IsBrightnessSupported (adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, IsBrightnessSupported);
	}
	ADLX_RESULT IsContrastSupported (adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, IsContrastSupported);
	}
	ADLX_RESULT IsHueSupported (adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, IsHueSupported);
	}
	ADLX_RESULT IsSaturationSupported (adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, IsSaturationSupported);
	}
	ADLX_RESULT IsTemperatureSupported (adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, IsTemperatureSupported);
	}
	ADLX_RESULT SetBrightness (adlx_int brightness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, SetBrightness);
	}
	ADLX_RESULT SetContrast (adlx_int contrast) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, SetContrast);
	}
	ADLX_RESULT SetHue (adlx_int hue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, SetHue);
	}
	ADLX_RESULT SetSaturation (adlx_int saturation) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, SetSaturation);
	}
	ADLX_RESULT SetTemperature (adlx_int temperature) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayCustomColor, SetTemperature);
	}
};
