// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

#include "../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "../../../SDK/Include/ISystem3.h"


namespace py = pybind11;
using namespace adlx;


class PyGPU : public IADLXGPU3
{
public:
	using IADLXGPU3::IADLXGPU3;

	ADLX_RESULT VendorId(const char** vendorid) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, VendorId);
	}

	ADLX_RESULT ASICFamilyType(ADLX_ASIC_FAMILY_TYPE* asicFamilyType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, ASICFamilyType);
	}

	ADLX_RESULT Type(ADLX_GPU_TYPE* gpuType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, Type);
	}

	ADLX_RESULT IsExternal(adlx_bool* isExternal) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, IsExternal);
	}

	ADLX_RESULT Name(const char** name) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, Name);
	}

	ADLX_RESULT DriverPath(const char** driverPath) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, DriverPath);
	}

	ADLX_RESULT PNPString(const char** pnpString) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, PNPString);
	}

	ADLX_RESULT HasDesktops(adlx_bool* hasDesktops) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, HasDesktops);
	}

	ADLX_RESULT TotalVRAM(adlx_uint* vramMB) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, TotalVRAM);
	}

	ADLX_RESULT VRAMType(const char** type) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, VRAMType);
	}

	ADLX_RESULT BIOSInfo(const char** partNumber, const char** version, const char** date) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, BIOSInfo);
	}

	ADLX_RESULT DeviceId(const char** deviceId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, DeviceId);
	}

	ADLX_RESULT RevisionId(const char** revisionId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, RevisionId);
	}

	ADLX_RESULT SubSystemId(const char** subSystemId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, SubSystemId);
	}

	ADLX_RESULT SubSystemVendorId(const char** subSystemVendorId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, SubSystemVendorId);
	}

	ADLX_RESULT UniqueId(adlx_int* uniqueId)  override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, UniqueId);
	}

    ADLX_RESULT PCIBusType(ADLX_PCI_BUS_TYPE* busType) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, PCIBusType);
    }

    ADLX_RESULT PCIBusLaneWidth(adlx_uint* laneWidth) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, PCIBusLaneWidth);
    }

    ADLX_RESULT MultiGPUMode(ADLX_MGPU_MODE* mode) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, MultiGPUMode);
    }

    ADLX_RESULT ProductName(const char** productName) const override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, ProductName);
    }

	// IADLXGPU2
	ADLX_RESULT IsPowerOff(adlx_bool* state) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, IsPowerOff);
	}
	ADLX_RESULT PowerOn() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, PowerOn);
	}
	ADLX_RESULT StartPowerOff(IADLXGPUConnectChangedListener* pGPUConnectChangedListener, adlx_int timeout) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, StartPowerOff);
	}
	ADLX_RESULT AbortPowerOff() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, AbortPowerOff);
	}
	ADLX_RESULT IsSupportedApplicationList(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, IsSupportedApplicationList);
	}
	ADLX_RESULT GetApplications(IADLXApplicationList** ppApplications) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, GetApplications);
	}
	ADLX_RESULT AMDSoftwareReleaseDate(adlx_uint* year, adlx_uint* month, adlx_uint* day) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, AMDSoftwareReleaseDate);
	}
	ADLX_RESULT AMDSoftwareEdition(const char** edition) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, AMDSoftwareEdition);
	}
	ADLX_RESULT AMDSoftwareVersion(const char** version) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, AMDSoftwareVersion);
	}
	ADLX_RESULT DriverVersion(const char** version) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, DriverVersion);
	}
	ADLX_RESULT AMDWindowsDriverVersion(const char** version) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, AMDWindowsDriverVersion);
	}
	ADLX_RESULT LUID(ADLX_LUID* luid) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, LUID);
	}

	// IADLXGPU3
	ADLX_RESULT MicroArchitecture(const char** microArchitecture) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, MicroArchitecture);
	}
	ADLX_RESULT HighestVRAMBandwidth(adlx_uint* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, HighestVRAMBandwidth);
	}
	ADLX_RESULT InvisibleVRAM(adlx_uint* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, InvisibleVRAM);
	}
	ADLX_RESULT VisibleVRAM(adlx_uint* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, VisibleVRAM);
	}
	ADLX_RESULT VRAMVendorRevId(adlx_uint* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, VRAMVendorRevId);
	}
	ADLX_RESULT VRAMBandwidth(adlx_uint* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, VRAMBandwidth);
	}
	ADLX_RESULT VRAMBitRate(adlx_uint* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, VRAMBitRate);
	}
	ADLX_RESULT IsSupportedStressTest(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, IsSupportedStressTest);
	}
	ADLX_RESULT StartStressTest(IADLXGPUStressTestFinishedListener* pGPUStressTestFinishedListener, adlx_uint duration) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU3, StartStressTest);
	}
};
