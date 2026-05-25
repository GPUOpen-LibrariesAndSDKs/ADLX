// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings3.h"


namespace py = pybind11;
using namespace adlx;


class Py3DSettingsChangedEvent : public IADLX3DSettingsChangedEvent3
{
public:
	using IADLX3DSettingsChangedEvent3::IADLX3DSettingsChangedEvent3;

	ADLX_RESULT    GetGPU (IADLXGPU** ppGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsChangedEvent3, GetGPU);
	}

	adlx_bool    IsAntiLagChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsAntiLagChanged);
	}

	adlx_bool   IsChillChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsChillChanged);
	}

	// IsBoostChanged
	adlx_bool   IsBoostChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsBoostChanged);
	}
	// IsImageSharpeningChanged
	adlx_bool   IsImageSharpeningChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsImageSharpeningChanged);
	}
	//IsEnhancedSyncChanged
	adlx_bool   IsEnhancedSyncChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsEnhancedSyncChanged);
	}
	//IsWaitForVerticalRefreshChanged
	adlx_bool   IsWaitForVerticalRefreshChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsWaitForVerticalRefreshChanged);
	}
	//IsFrameRateTargetControlChanged
	adlx_bool   IsFrameRateTargetControlChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsFrameRateTargetControlChanged);
	}
	// IsAntiAliasingChanged
	adlx_bool   IsAntiAliasingChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsAntiAliasingChanged);
	}
	// IsMorphologicalAntiAliasingChanged
	adlx_bool   IsMorphologicalAntiAliasingChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsMorphologicalAntiAliasingChanged);
	}
	//IsAnisotropicFilteringChanged
	adlx_bool   IsAnisotropicFilteringChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsAnisotropicFilteringChanged);
	}
	// IsTessellationModeChanged
	adlx_bool   IsTessellationModeChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsTessellationModeChanged);
	}
	// IsRadeonSuperResolutionChanged
	adlx_bool   IsRadeonSuperResolutionChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsRadeonSuperResolutionChanged);
	}
	//IsResetShaderCache
	adlx_bool   IsResetShaderCache() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsResetShaderCache);
	}
	// IsAMDFluidMotionFramesChanged
	adlx_bool   IsAMDFluidMotionFramesChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsAMDFluidMotionFramesChanged);
	}
	// IsImageSharpenDesktopChanged
	adlx_bool   IsImageSharpenDesktopChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsImageSharpenDesktopChanged);
	}
	// IsFidelityFXSuperResolutionChanged
	adlx_bool   IsFidelityFXSuperResolutionChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsFidelityFXSuperResolutionChanged);
	}
	// IsFidelityFXFrameGenUpgradeChanged
	adlx_bool   IsFidelityFXFrameGenUpgradeChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLX3DSettingsChangedEvent3, IsFidelityFXFrameGenUpgradeChanged);
	}

	ADLX_SYNC_ORIGIN GetOrigin() override {
		PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLX3DSettingsChangedEvent3, GetOrigin);
	}
};
