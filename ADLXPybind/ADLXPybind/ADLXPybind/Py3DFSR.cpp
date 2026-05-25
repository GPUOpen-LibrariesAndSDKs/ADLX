// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings3.h"


namespace py = pybind11;
using namespace adlx;


class Py3DFidelityFXSuperResolution : IADLX3DFidelityFXSuperResolution
{
public:
	using IADLX3DFidelityFXSuperResolution::IADLX3DFidelityFXSuperResolution;

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXSuperResolution, IsSupported);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXSuperResolution, IsEnabled);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXSuperResolution, SetEnabled);
	}
};

class Py3DFidelityFXFrameGenUpgradeRatioOption : IADLX3DFidelityFXFrameGenUpgradeRatioOption
{
public:
	using IADLX3DFidelityFXFrameGenUpgradeRatioOption::IADLX3DFidelityFXFrameGenUpgradeRatioOption;

	ADLX_RESULT Ratio(ADLX_FFX_FRAME_GEN_RATIO* ratio) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgradeRatioOption, Ratio);
	}
};

class Py3DFidelityFXFrameGenUpgradeRatioOptionList : public IADLX3DFidelityFXFrameGenUpgradeRatioOptionList
{
public:
	using IADLX3DFidelityFXFrameGenUpgradeRatioOptionList::IADLX3DFidelityFXFrameGenUpgradeRatioOptionList;

	ADLX_RESULT Add_Back(IADLX3DFidelityFXFrameGenUpgradeRatioOption* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgradeRatioOptionList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLX3DFidelityFXFrameGenUpgradeRatioOption** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgradeRatioOptionList, At);
	}
};

class Py3DFidelityFXFrameGenUpgrade : IADLX3DFidelityFXFrameGenUpgrade
{
public:
	using IADLX3DFidelityFXFrameGenUpgrade::IADLX3DFidelityFXFrameGenUpgrade;

	ADLX_RESULT GetAvailableRatios(IADLX3DFidelityFXFrameGenUpgradeRatioOptionList** ratios) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgrade, GetAvailableRatios);
	}

	ADLX_RESULT GetRatio(ADLX_FFX_FRAME_GEN_RATIO* ratio) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgrade, GetRatio);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgrade, IsSupported);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgrade, IsEnabled);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgrade, SetEnabled);
	}

	ADLX_RESULT SetRatio(ADLX_FFX_FRAME_GEN_RATIO ratio) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFidelityFXFrameGenUpgrade, SetRatio);
	}
};