// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDesktops.h"


namespace py = pybind11;
using namespace adlx;


class PySimpleEyefinity : public IADLXSimpleEyefinity
{
public:
	using IADLXSimpleEyefinity::IADLXSimpleEyefinity;

	ADLX_RESULT Create(IADLXEyefinityDesktop** ppEyefinityDesktop) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSimpleEyefinity, Create);
	}

	ADLX_RESULT Destroy(IADLXEyefinityDesktop* pDesktop) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSimpleEyefinity, Destroy);
	}

	ADLX_RESULT DestroyAll() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSimpleEyefinity, DestroyAll);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSimpleEyefinity, IsSupported);
	}
};
