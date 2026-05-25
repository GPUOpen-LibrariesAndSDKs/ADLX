// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplay3DLUT.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplay3DLUT : public IADLXDisplay3DLUT
{
public:
	using IADLXDisplay3DLUT::IADLXDisplay3DLUT;

	ADLX_RESULT ClearUser3DLUT() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, ClearUser3DLUT);
	}

	ADLX_RESULT GetAllUser3DLUT(ADLX_3DLUT_TRANSFER_FUNCTION* transferFunction, ADLX_3DLUT_COLORSPACE* colorSpace, adlx_int* pointsNumber, ADLX_3DLUT_Data* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, GetAllUser3DLUT);
	}

	ADLX_RESULT GetHDRUser3DLUT(ADLX_3DLUT_TRANSFER_FUNCTION* transferFunction, ADLX_3DLUT_COLORSPACE* colorSpace, adlx_int* pointsNumber, ADLX_3DLUT_Data* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, GetHDRUser3DLUT);
	}

	ADLX_RESULT GetSCEDynamicContrast(adlx_int* contrast) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, GetSCEDynamicContrast);
	}

	ADLX_RESULT GetSCEDynamicContrastRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, GetSCEDynamicContrastRange);
	}

	ADLX_RESULT GetSDRUser3DLUT(ADLX_3DLUT_TRANSFER_FUNCTION* transferFunction, ADLX_3DLUT_COLORSPACE* colorSpace, adlx_int* pointsNumber, ADLX_3DLUT_Data* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, GetSDRUser3DLUT);
	}

	ADLX_RESULT GetUser3DLUTIndex(adlx_int lutSize, const ADLX_UINT16_RGB* rgbCoordinate, adlx_int* index) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, GetUser3DLUTIndex);
	}

	ADLX_RESULT IsCurrentSCEDisabled(adlx_bool* sceDisabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, IsCurrentSCEDisabled);
	}

	ADLX_RESULT IsCurrentSCEDynamicContrast(adlx_bool* dynamicContrast) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, IsCurrentSCEDynamicContrast);
	}

	ADLX_RESULT IsCurrentSCEVividGaming(adlx_bool* vividGaming) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, IsCurrentSCEVividGaming);
	}

	ADLX_RESULT IsSupportedSCE(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, IsSupportedSCE);
	}

	ADLX_RESULT IsSupportedSCEDynamicContrast(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, IsSupportedSCEDynamicContrast);
	}

	ADLX_RESULT IsSupportedSCEVividGaming(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, IsSupportedSCEVividGaming);
	}

	ADLX_RESULT IsSupportedUser3DLUT(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, IsSupportedUser3DLUT);
	}

	ADLX_RESULT SetAllUser3DLUT(ADLX_3DLUT_TRANSFER_FUNCTION transferFunction, ADLX_3DLUT_COLORSPACE colorSpace, adlx_int pointsNumber, const ADLX_3DLUT_Data* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, SetAllUser3DLUT);
	}

	ADLX_RESULT SetHDRUser3DLUT(ADLX_3DLUT_TRANSFER_FUNCTION transferFunction, ADLX_3DLUT_COLORSPACE colorSpace, adlx_int pointsNumber, const ADLX_3DLUT_Data* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, SetHDRUser3DLUT);
	}

	ADLX_RESULT SetSCEDisabled() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, SetSCEDisabled);
	}

	ADLX_RESULT SetSCEDynamicContrast(adlx_int contrast) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, SetSCEDynamicContrast);
	}

	ADLX_RESULT SetSCEVividGaming() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, SetSCEVividGaming);
	}

	ADLX_RESULT SetSDRUser3DLUT(ADLX_3DLUT_TRANSFER_FUNCTION transferFunction, ADLX_3DLUT_COLORSPACE colorSpace, adlx_int pointsNumber, const ADLX_3DLUT_Data* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUT, SetSDRUser3DLUT);
	}


};
