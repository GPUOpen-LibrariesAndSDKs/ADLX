// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayBlanking : public IADLXDisplayBlanking
{
public:
	using IADLXDisplayBlanking::IADLXDisplayBlanking;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayBlanking, IsSupported);
    }

	ADLX_RESULT IsCurrentBlanked(adlx_bool* blanked) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayBlanking, IsCurrentBlanked);
	}

	ADLX_RESULT IsCurrentUnblanked(adlx_bool* unBlanked) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayBlanking, IsCurrentUnblanked);
	}

    ADLX_RESULT SetBlanked() override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayBlanking, SetBlanked);
    }

    ADLX_RESULT SetUnblanked() override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayBlanking, SetUnblanked);
    }
};
