// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring.h"


namespace py = pybind11;
using namespace adlx;


class PyFPS : IADLXFPS
{
public:
	using IADLXFPS::IADLXFPS;

	ADLX_RESULT FPS(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXFPS, FPS);
	}

	ADLX_RESULT TimeStamp(adlx_int64* ms) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXFPS, TimeStamp);
	}
};
