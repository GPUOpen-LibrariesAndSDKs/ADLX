// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DResetShaderCache : public IADLX3DResetShaderCache
{
public:
	using IADLX3DResetShaderCache::IADLX3DResetShaderCache;

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DResetShaderCache, IsSupported);
	}

	ADLX_RESULT ResetShaderCache() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DResetShaderCache, ResetShaderCache);
	}
};
