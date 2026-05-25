// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IApplications.h"


namespace py = pybind11;
using namespace adlx;


class PyApplication : IADLXApplication
{
public:
	using IADLXApplication::IADLXApplication;

	ADLX_RESULT ProcessID(adlx_ulong* pid) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXApplication, ProcessID);
	}

	ADLX_RESULT Name(const wchar_t** ppAppName) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXApplication, Name);
	}

    ADLX_RESULT FullPath(const wchar_t** ppAppPath) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXApplication, FullPath);
    }

    ADLX_RESULT GPUDependencyType(ADLX_APP_GPU_DEPENDENCY* gpuDependency) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXApplication, GPUDependencyType);
    }
};
