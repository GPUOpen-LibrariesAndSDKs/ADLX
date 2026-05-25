// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplayGamut.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayGamut : public IADLXDisplayGamut
{
public:
	using IADLXDisplayGamut::IADLXDisplayGamut;

	ADLX_RESULT GetGamutColorSpace(ADLX_GamutColorSpace* gamutColorSpace) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, GetGamutColorSpace);
	}

	ADLX_RESULT    GetWhitePoint(ADLX_Point* point) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, GetWhitePoint);
	}

	ADLX_RESULT    IsCurrent5000kWhitePoint(adlx_bool* isSet) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrent5000kWhitePoint);
	}

	ADLX_RESULT    IsCurrent6500kWhitePoint(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrent6500kWhitePoint);
	}

	ADLX_RESULT    IsCurrent7500kWhitePoint(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrent7500kWhitePoint);
	}

	ADLX_RESULT    IsCurrent9300kWhitePoint(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrent9300kWhitePoint);
	}

	ADLX_RESULT    IsCurrentAdobeRgbColorSpace(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrentAdobeRgbColorSpace);
	}

	ADLX_RESULT    IsCurrentCCIR2020ColorSpace(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrentCCIR2020ColorSpace);
	}

	ADLX_RESULT    IsCurrentCCIR601ColorSpace(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrentCCIR601ColorSpace);
	}

	ADLX_RESULT    IsCurrentCCIR709ColorSpace(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrentCCIR709ColorSpace);
	}

	ADLX_RESULT    IsCurrentCIERgbColorSpace(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrentCIERgbColorSpace);
	}

	ADLX_RESULT    IsCurrentCustomColorSpace(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrentCustomColorSpace);
	}

	ADLX_RESULT    IsCurrentCustomWhitePoint(adlx_bool* isSet)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsCurrentCustomWhitePoint);
	}

	ADLX_RESULT    IsSupported5000kWhitePoint(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupported5000kWhitePoint);
	}

	ADLX_RESULT    IsSupported6500kWhitePoint(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupported6500kWhitePoint);
	}

	ADLX_RESULT    IsSupported7500kWhitePoint(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupported7500kWhitePoint);
	}

	ADLX_RESULT    IsSupported9300kWhitePoint(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupported9300kWhitePoint);
	}

	ADLX_RESULT    IsSupportedAdobeRgbColorSpace(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupportedAdobeRgbColorSpace);
	}

	ADLX_RESULT    IsSupportedCCIR2020ColorSpace(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupportedCCIR2020ColorSpace);
	}

	ADLX_RESULT    IsSupportedCCIR601ColorSpace(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupportedCCIR601ColorSpace);
	}

	ADLX_RESULT    IsSupportedCCIR709ColorSpace(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupportedCCIR709ColorSpace);
	}

	ADLX_RESULT    IsSupportedCIERgbColorSpace(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupportedCIERgbColorSpace);
	}

	ADLX_RESULT    IsSupportedCustomColorSpace(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupportedCustomColorSpace);
	}

	ADLX_RESULT    IsSupportedCustomWhitePoint(adlx_bool* supported)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, IsSupportedCustomWhitePoint);
	}

	ADLX_RESULT    SetGamut1(ADLX_RGB customWhitePoint, ADLX_GamutColorSpace customGamut)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, SetGamut1);
	}

	ADLX_RESULT    SetGamut2(ADLX_RGB customWhitePoint, ADLX_GAMUT_SPACE predefinedGamutSpace)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, SetGamut2);
	}

	ADLX_RESULT    SetGamut3(ADLX_WHITE_POINT predefinedWhitePoint, ADLX_GamutColorSpace customGamut)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, SetGamut3);
	}

	ADLX_RESULT    SetGamut4(ADLX_WHITE_POINT predefinedWhitePoint, ADLX_GAMUT_SPACE predefinedGamutSpace)
	{
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGamut, SetGamut4);
	}

};
