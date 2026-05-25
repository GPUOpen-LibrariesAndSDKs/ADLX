//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/II2C.h"


namespace py = pybind11;
using namespace adlx;


class PyI2C : public IADLXI2C
{
public:
	using IADLXI2C::IADLXI2C;

	ADLX_RESULT IsSupported(ADLX_I2C_LINE line, adlx_int address, adlx_bool* isSupported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXI2C, IsSupported);
	}

	ADLX_RESULT Read(ADLX_I2C_LINE line, adlx_int speed, adlx_int address, adlx_int offset, adlx_int dataSize, adlx_byte* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXI2C, Read);
	}

	ADLX_RESULT RepeatedStartRead(ADLX_I2C_LINE line, adlx_int speed, adlx_int address, adlx_int offset, adlx_int dataSize, adlx_byte* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXI2C, RepeatedStartRead);
	}

	ADLX_RESULT Version(adlx_int* major, adlx_int* minor) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXI2C, Version);
	}

	ADLX_RESULT Write(ADLX_I2C_LINE line, adlx_int speed, adlx_int address, adlx_int offset, adlx_int dataSize, adlx_byte* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXI2C, Write);
	}
};
