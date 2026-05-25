// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplayGamma.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayGamma : public IADLXDisplayGamma
{
public:
	using IADLXDisplayGamma::IADLXDisplayGamma;

	ADLX_RESULT GetGammaCoefficient(ADLX_RegammaCoeff* coeff) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, GetGammaCoefficient);
	}
	ADLX_RESULT GetGammaRamp(ADLX_GammaRamp* lut) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, GetGammaRamp);
	}
	ADLX_RESULT IsCurrentDeGammaRamp(adlx_bool* isDeGammaRamp) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentDeGammaRamp);
	}
	ADLX_RESULT IsCurrentReGamma36(adlx_bool* isCurrentReGamma36) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentReGamma36);
	}
	ADLX_RESULT IsCurrentReGammaBT709(adlx_bool* isCurrentReGammaBT709) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentReGammaBT709);
	}
	ADLX_RESULT IsCurrentReGammaPQ(adlx_bool* isCurrentReGammaPQ) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentReGammaPQ);
	}
	ADLX_RESULT IsCurrentReGammaPQ2084Interim(adlx_bool* isCurrentReGammaPQ2084Interim) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentReGammaPQ2084Interim);
	}
	ADLX_RESULT IsCurrentReGammaRamp(adlx_bool* isReGammaRamp) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentReGammaRamp);
	}
	ADLX_RESULT IsCurrentReGammaSRGB(adlx_bool* isCurrentReGammaSRGB) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentReGammaSRGB);
	}
	ADLX_RESULT IsCurrentRegammaCoefficient(adlx_bool* isRegammaCoeff) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsCurrentRegammaCoefficient);
	}
	ADLX_RESULT IsSupportedReGamma36(adlx_bool* isSupportedReGamma36) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsSupportedReGamma36);
	}
	ADLX_RESULT IsSupportedReGammaBT709(adlx_bool* isSupportedReGammaBT709) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsSupportedReGammaBT709);
	}
	ADLX_RESULT IsSupportedReGammaPQ(adlx_bool* isSupportedReGammaPQ) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsSupportedReGammaPQ);
	}
	ADLX_RESULT IsSupportedReGammaPQ2084Interim(adlx_bool* isSupportedReGammaPQ2084Interim) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsSupportedReGammaPQ2084Interim);
	}
	ADLX_RESULT IsSupportedReGammaSRGB(adlx_bool* isSupportedRegammaSRGB) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, IsSupportedReGammaSRGB);
	}
	ADLX_RESULT ResetGammaRamp() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, ResetGammaRamp);
	}
	ADLX_RESULT SetDeGammaRampFile(const char* path) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetDeGammaRampFile);
	}
	ADLX_RESULT SetDeGammaRampMemory(ADLX_GammaRamp gammaRamp) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetDeGammaRampMemory);
	}
	ADLX_RESULT SetReGamma36() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGamma36);
	}
	ADLX_RESULT SetReGammaBT709() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGammaBT709);
	}
	ADLX_RESULT SetReGammaCoefficient(ADLX_RegammaCoeff coeff) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGammaCoefficient);
	}
	ADLX_RESULT SetReGammaPQ() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGammaPQ);
	}
	ADLX_RESULT SetReGammaPQ2084Interim() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGammaPQ2084Interim);
	}
	ADLX_RESULT SetReGammaRampFile(const char* path) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGammaRampFile);
	}
	ADLX_RESULT SetReGammaRampMemory(ADLX_GammaRamp gammaRamp) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGammaRampMemory);
	}
	ADLX_RESULT SetReGammaSRGB() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamma, SetReGammaSRGB);
	}
};
