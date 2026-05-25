// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayVariBright : public IADLXDisplayVariBright1
{
public:
	using IADLXDisplayVariBright1::IADLXDisplayVariBright1;

	ADLX_RESULT IsCurrentBalanced(adlx_bool* balanced) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsCurrentBalanced);
	}
	ADLX_RESULT IsCurrentMaximizeBattery(adlx_bool* maximizeBattery) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsCurrentMaximizeBattery);
	}
	ADLX_RESULT IsCurrentMaximizeBrightness(adlx_bool* maximizeBrightness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsCurrentMaximizeBrightness);
	}
	ADLX_RESULT IsCurrentOptimizeBattery(adlx_bool* optimizeBattery) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsCurrentOptimizeBattery);
	}
	ADLX_RESULT IsCurrentOptimizeBrightness(adlx_bool* optimizeBrightness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsCurrentOptimizeBrightness);
	}
	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsEnabled);
	}
	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsSupported);
	}
	ADLX_RESULT SetBalanced() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetBalanced);
	}
	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetEnabled);
	}
	ADLX_RESULT SetMaximizeBattery() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetMaximizeBattery);
	}
	ADLX_RESULT SetMaximizeBrightness() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetMaximizeBrightness);
	}
	ADLX_RESULT SetOptimizeBattery() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetOptimizeBattery);
	}
	ADLX_RESULT SetOptimizeBrightness() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetOptimizeBrightness);
	}

	// IADLXDisplayVariBright1
	ADLX_RESULT IsBacklightAdaptiveSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsBacklightAdaptiveSupported);
	}
	ADLX_RESULT IsBacklightAdaptiveEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsBacklightAdaptiveEnabled);
	}
	ADLX_RESULT SetBacklightAdaptiveEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetBacklightAdaptiveEnabled);
	}
	ADLX_RESULT IsBatteryLifeSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsBatteryLifeSupported);
	}
	ADLX_RESULT IsBatteryLifeEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsBatteryLifeEnabled);
	}
	ADLX_RESULT SetBatteryLifeEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetBatteryLifeEnabled);
	}
	ADLX_RESULT IsWindowsPowerModeSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsWindowsPowerModeSupported);
	}
	ADLX_RESULT IsWindowsPowerModeEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsWindowsPowerModeEnabled);
	}
	ADLX_RESULT SetWindowsPowerModeEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetWindowsPowerModeEnabled);
	}
	ADLX_RESULT IsFullScreenVideoSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsFullScreenVideoSupported);
	}
	ADLX_RESULT IsFullScreenVideoEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, IsFullScreenVideoEnabled);
	}
	ADLX_RESULT SetFullScreenVideoEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVariBright1, SetFullScreenVideoEnabled);
	}
};
