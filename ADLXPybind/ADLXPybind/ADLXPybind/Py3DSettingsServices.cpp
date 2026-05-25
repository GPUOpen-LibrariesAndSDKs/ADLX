// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings3.h"


namespace py = pybind11;
using namespace adlx;


class Py3DSettingsServices : IADLX3DSettingsServices3
{
public:
	using IADLX3DSettingsServices3::IADLX3DSettingsServices3;
	
	ADLX_RESULT Get3DSettingsChangedHandling(IADLX3DSettingsChangedHandling** pp3DSettingsChangedHandling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, Get3DSettingsChangedHandling);
	}

	ADLX_RESULT GetAnisotropicFiltering(IADLXGPU* pGPU, IADLX3DAnisotropicFiltering** pp3DAnisotropicFiltering) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetAnisotropicFiltering);
	}

	ADLX_RESULT GetAntiAliasing(IADLXGPU* pGPU, IADLX3DAntiAliasing** pp3DAntiAliasing) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetAntiAliasing);
	}

	ADLX_RESULT GetAntiLag(IADLXGPU* pGPU, IADLX3DAntiLag** pp3DAntiLag) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetAntiLag);
	}

	ADLX_RESULT GetBoost(IADLXGPU* pGPU, IADLX3DBoost** pp3DBoost) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetBoost);
	}

	ADLX_RESULT GetChill(IADLXGPU* pGPU, IADLX3DChill** pp3DChill) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetChill);
	}

	ADLX_RESULT GetEnhancedSync(IADLXGPU* pGPU, IADLX3DEnhancedSync** pp3DEnhancedSync) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetEnhancedSync);
	}

	ADLX_RESULT GetFrameRateTargetControl(IADLXGPU* pGPU, IADLX3DFrameRateTargetControl** pp3DFrameRateTargetControl) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetFrameRateTargetControl);
	}
	
	ADLX_RESULT GetImageSharpening(IADLXGPU* pGPU, IADLX3DImageSharpening** pp3DImageSharpening) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetImageSharpening);
	}
	
    ADLX_RESULT GetImageSharpenDesktop(IADLXGPU* pGPU, IADLX3DImageSharpenDesktop** pp3DImageSharpenDesktop) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetImageSharpenDesktop);
    }

	ADLX_RESULT GetMorphologicalAntiAliasing(IADLXGPU* pGPU, IADLX3DMorphologicalAntiAliasing** pp3DMorphologicalAntiAliasing) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetMorphologicalAntiAliasing);
	}
	
	ADLX_RESULT GetRadeonSuperResolution(IADLX3DRadeonSuperResolution** pp3DRadeonSuperResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetRadeonSuperResolution);
	}

	ADLX_RESULT GetResetShaderCache(IADLXGPU* pGPU, IADLX3DResetShaderCache** pp3DResetShaderCache) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetResetShaderCache);
	}
	
	ADLX_RESULT GetTessellation(IADLXGPU* pGPU, IADLX3DTessellation** pp3DTessellation) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetTessellation);
	}
	
	ADLX_RESULT GetWaitForVerticalRefresh(IADLXGPU* pGPU, IADLX3DWaitForVerticalRefresh** pp3DWaitForVerticalRefresh) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetWaitForVerticalRefresh);
	}

    ADLX_RESULT GetAMDFluidMotionFrames(IADLX3DAMDFluidMotionFrames** pp3DAMDFluidMotionFrames) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetAMDFluidMotionFrames);
    }

	ADLX_RESULT GetFidelityFXSuperResolution(IADLXGPU* pGPU, IADLX3DFidelityFXSuperResolution** ppFidelityFXSuperResolution) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetFidelityFXSuperResolution);
    }

	ADLX_RESULT GetFidelityFXFrameGenUpgrade(IADLXGPU* pGPU, IADLX3DFidelityFXFrameGenUpgrade** ppFidelityFXFrameGenUpgrade) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices3, GetFidelityFXFrameGenUpgrade);
    }
};