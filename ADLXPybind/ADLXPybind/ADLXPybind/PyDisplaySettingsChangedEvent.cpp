// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays3.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplaySettingsChangedEvent : public IADLXDisplaySettingsChangedEvent3
{
public:
	using IADLXDisplaySettingsChangedEvent3::IADLXDisplaySettingsChangedEvent3;

	ADLX_RESULT    GetDisplay(IADLXDisplay** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplaySettingsChangedEvent3, GetDisplay);
	}

	adlx_bool    IsColorDepthChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsColorDepthChanged);
	}

	adlx_bool    IsCustomColorBrightnessChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsCustomColorBrightnessChanged);
	}

	adlx_bool    IsCustomColorContrastChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsCustomColorContrastChanged);
	}

	adlx_bool    IsCustomColorHueChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsCustomColorHueChanged);
	}

	adlx_bool    IsCustomColorSaturationChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsCustomColorSaturationChanged);
	}

	adlx_bool    IsCustomColorTemperatureChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsCustomColorTemperatureChanged);
	}

	adlx_bool    IsCustomResolutionChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsCustomResolutionChanged);
	}

	adlx_bool    IsFreeSyncChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsFreeSyncChanged);
	}

	adlx_bool    IsGPUScalingChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsGPUScalingChanged);
	}

	adlx_bool    IsHDCPChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsHDCPChanged);
	}

	adlx_bool    IsIntegerScalingChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsIntegerScalingChanged);
	}

	adlx_bool    IsPixelFormatChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsPixelFormatChanged);
	}

	adlx_bool    IsScalingModeChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsScalingModeChanged);
	}

	adlx_bool    IsVSRChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsVSRChanged);
	}

	adlx_bool    IsVariBrightChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsVariBrightChanged);
	}

	// IADLXDisplaySettingsChangedEvent1
	adlx_bool    IsDisplayBlankingChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsDisplayBlankingChanged);
	}

	// IADLXDisplaySettingsChangedEvent2
	adlx_bool    IsDisplayConnectivityExperienceChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsDisplayConnectivityExperienceChanged);
	}

	// IADLXDisplaySettingsChangedEvent3
	adlx_bool    IsDisplayDynamicRefreshRateControlChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsDisplayDynamicRefreshRateControlChanged);
	}

	adlx_bool    IsFreeSyncColorAccuracyChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplaySettingsChangedEvent3, IsFreeSyncColorAccuracyChanged);
	}

	ADLX_SYNC_ORIGIN GetOrigin() override {
		PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLXDisplaySettingsChangedEvent3, GetOrigin);
	}
};
