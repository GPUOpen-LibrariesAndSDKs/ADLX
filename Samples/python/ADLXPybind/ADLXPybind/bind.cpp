//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

// Include pybind11 depends
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "../../../../SDK/Include/IDisplays.h"
#include "../../../../SDK/Include/I3DSettings.h"
#include "../../../../SDK/Include/ISystem.h"
#include "../../../../SDK/Include/IDisplaySettings.h"
#include "../../../../SDK/Include/I3DSettings1.h"

namespace py = pybind11;
using namespace adlx;

// Always needed for custom holder types
PYBIND11_DECLARE_HOLDER_TYPE(T, IADLXInterfacePtr_T<T>, true);

// Only needed if the type's `.get()` goes by another name
namespace pybind11 {
	namespace detail {
		template <typename T>
		struct holder_helper<IADLXInterfacePtr_T<T>> { // <-- specialization
			static const T *get(const IADLXInterfacePtr_T<T> &p) { return p.GetPtr(); }
		};
	}
}

class PySystem : public IADLXSystem
{
public:
	using IADLXSystem::IADLXSystem;

	ADLX_RESULT  HybridGraphicsType(ADLX_HG_TYPE* hgType)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			HybridGraphicsType
		);
	}

	ADLX_RESULT  GetGPUs(IADLXGPUList** ppGPUs)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUs
		);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			QueryInterface
		);
	}

	ADLX_RESULT  GetDisplaysServices(IADLXDisplayServices** ppDispServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetDisplaysServices
		);
	}

	ADLX_RESULT  GetDesktopsServices(IADLXDesktopServices** ppDeskServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetDesktopsServices
		);
	}

	ADLX_RESULT  GetGPUsChangedHandling(IADLXGPUsChangedHandling** ppGPUsChangedHandling)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUsChangedHandling
		);
	}

	ADLX_RESULT  EnableLog(ADLX_LOG_DESTINATION mode, ADLX_LOG_SEVERITY severity, IADLXLog* pLogger, const wchar_t* fileName)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			EnableLog
		);
	}

	ADLX_RESULT  Get3DSettingsServices(IADLX3DSettingsServices** pp3DSettingsServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			Get3DSettingsServices
		);
	}

	ADLX_RESULT  GetGPUTuningServices(IADLXGPUTuningServices** ppGPUTuningServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUTuningServices
		);
	}

	ADLX_RESULT  GetPerformanceMonitoringServices(IADLXPerformanceMonitoringServices** ppPerformanceMonitoringServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetPerformanceMonitoringServices
		);
	}

	ADLX_RESULT  TotalSystemRAM(adlx_uint* ramMB)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			TotalSystemRAM
		);
	}

	ADLX_RESULT  GetI2C(IADLXGPU *pGPU, IADLXI2C **ppI2C) override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetI2C
		);
	}
};

class PyDisplayService : public IADLXDisplayServices
{
public:
	using IADLXDisplayServices::IADLXDisplayServices;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT GetNumberOfDisplays(adlx_uint* numDisplays) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetNumberOfDisplays);
	}

	ADLX_RESULT GetDisplays(IADLXDisplayList** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetDisplays);
	}

	ADLX_RESULT Get3DLUT(IADLXDisplay* pDisplay, IADLXDisplay3DLUT** ppDisp3DLUT) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, Get3DLUT);
	}

	ADLX_RESULT GetGamut(IADLXDisplay* pDisplay, IADLXDisplayGamut** ppDispGamut) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGamut);
	}

	ADLX_RESULT GetGamma(IADLXDisplay* pDisplay, IADLXDisplayGamma** ppDispGamma) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGamma);
	}

	ADLX_RESULT GetDisplayChangedHandling(IADLXDisplayChangedHandling** ppDisplayChangeHandling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetDisplayChangedHandling);
	}

	ADLX_RESULT  GetFreeSync(IADLXDisplay* pDisplay, IADLXDisplayFreeSync** ppFreeSync) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetFreeSync);
	}

	ADLX_RESULT  GetVirtualSuperResolution(IADLXDisplay* pDisplay, IADLXDisplayVSR** ppVSR) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetVirtualSuperResolution);
	}

	ADLX_RESULT  GetGPUScaling(IADLXDisplay* pDisplay, IADLXDisplayGPUScaling** ppGPUScaling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGPUScaling);
	}

	ADLX_RESULT  GetScalingMode(IADLXDisplay* pDisplay, IADLXDisplayScalingMode** ppScalingMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetScalingMode);
	}

	ADLX_RESULT  GetIntegerScaling(IADLXDisplay* pDisplay, IADLXDisplayIntegerScaling** ppIntegerScaling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetIntegerScaling);
	}

	ADLX_RESULT  GetColorDepth(IADLXDisplay* pDisplay, IADLXDisplayColorDepth** ppColorDepth) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetColorDepth);
	}

	ADLX_RESULT  GetPixelFormat(IADLXDisplay* pDisplay, IADLXDisplayPixelFormat** ppPixelFormat) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetPixelFormat);
	}

	ADLX_RESULT  GetCustomColor(IADLXDisplay* pDisplay, IADLXDisplayCustomColor** ppCustomColor) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetCustomColor);
	}

	ADLX_RESULT  GetHDCP(IADLXDisplay* pDisplay, IADLXDisplayHDCP** ppHDCP) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetHDCP);
	}

	ADLX_RESULT  GetCustomResolution(IADLXDisplay* pDisplay, IADLXDisplayCustomResolution** ppCustomResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetCustomResolution);
	}

    ADLX_RESULT  GetVariBright(IADLXDisplay* pDisplay, IADLXDisplayVariBright** ppVariBright) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetVariBright);
    }
};

class PyGPU : public IADLXGPU
{
public:
	using IADLXGPU::IADLXGPU;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  VendorId(const char** vendorId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, VendorId);
	}

	ADLX_RESULT  ASICFamilyType(ADLX_ASIC_FAMILY_TYPE* asicFamilyType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, ASICFamilyType);
	}

	ADLX_RESULT  Type(ADLX_GPU_TYPE* gpuType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, Type);
	}

	ADLX_RESULT  IsExternal(adlx_bool* isExternal) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, IsExternal);
	}

	ADLX_RESULT  Name(const char** displayName) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, Name);
	}

	ADLX_RESULT  DriverPath(const char** driverPath) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, DriverPath);
	}

	ADLX_RESULT  PNPString(const char** pnpString) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, PNPString);
	}

	ADLX_RESULT  HasDesktops(adlx_bool* hasDesktops) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, HasDesktops);
	}

	ADLX_RESULT  TotalVRAM(adlx_uint* vramMB) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, TotalVRAM);
	}

	ADLX_RESULT  VRAMType(const char** type) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, VRAMType);
	}

	ADLX_RESULT  BIOSInfo(const char** partNumber, const char** version, const char** date) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, BIOSInfo);
	}

	ADLX_RESULT  DeviceId(const char** deviceId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, DeviceId);
	}

	ADLX_RESULT  RevisionId(const char** revisionId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, RevisionId);
	}

	ADLX_RESULT  SubSystemId(const char** subSystemId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, SubSystemId);
	}

	ADLX_RESULT  SubSystemVendorId(const char** subSystemVendorId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, SubSystemVendorId);
	}

	ADLX_RESULT  UniqueId(adlx_int* uniqueId) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPU, UniqueId);
	}
};

class Py3DAntiLag : public IADLX3DAntiLag
{
public:
	using IADLX3DAntiLag::IADLX3DAntiLag;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag, IsSupported);
	}

	ADLX_RESULT  IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag, IsEnabled);
	}

	ADLX_RESULT  SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag, SetEnabled);
	}
};

class Py3DChill : public IADLX3DChill
{
public:
	using IADLX3DChill::IADLX3DChill;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, IsSupported);
	}

	ADLX_RESULT  IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, IsEnabled);
	}

	ADLX_RESULT  GetFPSRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, GetFPSRange);
	}

	ADLX_RESULT  GetMinFPS(adlx_int* currentMinFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, GetMinFPS);
	}

	ADLX_RESULT  GetMaxFPS(adlx_int* currentMaxFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, GetMaxFPS);
	}

	ADLX_RESULT  SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, SetEnabled);
	}

	ADLX_RESULT  SetMinFPS(adlx_int minFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, SetMinFPS);
	}

	ADLX_RESULT  SetMaxFPS(adlx_int maxFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, SetMaxFPS);
	}
};

class Py3DBoost : public IADLX3DBoost
{
public:
	using IADLX3DBoost::IADLX3DBoost;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, IsSupported);
	}

	ADLX_RESULT  IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, IsEnabled);
	}

	ADLX_RESULT  GetResolutionRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, GetResolutionRange);
	}

	ADLX_RESULT  GetResolution(adlx_int* currentMinRes) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, GetResolution);
	}

	ADLX_RESULT  SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, SetEnabled);
	}

	ADLX_RESULT  SetResolution(adlx_int minRes) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, SetResolution);
	}
};

class Py3DSettingsServices : public IADLX3DSettingsServices
{
public:
	using IADLX3DSettingsServices::IADLX3DSettingsServices;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  GetAntiLag(IADLXGPU* pGPU, IADLX3DAntiLag** pp3DAntiLag) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetAntiLag);
	}

	ADLX_RESULT  GetChill(IADLXGPU* pGPU, IADLX3DChill** pp3DChill) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetChill);
	}

	ADLX_RESULT  GetBoost(IADLXGPU* pGPU, IADLX3DBoost** pp3DBoost) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetBoost);
	}

	ADLX_RESULT  GetImageSharpening(IADLXGPU* pGPU, IADLX3DImageSharpening** pp3DImageSharpening) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetImageSharpening);
	}

	ADLX_RESULT  GetEnhancedSync(IADLXGPU* pGPU, IADLX3DEnhancedSync** pp3DEnhancedSync) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetEnhancedSync);
	}

	ADLX_RESULT  GetWaitForVerticalRefresh(IADLXGPU* pGPU, IADLX3DWaitForVerticalRefresh** pp3DWaitForVerticalRefresh) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetWaitForVerticalRefresh);
	}

	ADLX_RESULT  GetFrameRateTargetControl(IADLXGPU* pGPU, IADLX3DFrameRateTargetControl** pp3DFrameRateTargetControl) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetFrameRateTargetControl);
	}

	ADLX_RESULT  GetAntiAliasing(IADLXGPU* pGPU, IADLX3DAntiAliasing** pp3DAntiAliasing) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetAntiAliasing);
	}

	ADLX_RESULT  GetMorphologicalAntiAliasing(IADLXGPU* pGPU, IADLX3DMorphologicalAntiAliasing** pp3DMorphologicalAntiAliasing) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetMorphologicalAntiAliasing);
	}

	ADLX_RESULT  GetAnisotropicFiltering(IADLXGPU* pGPU, IADLX3DAnisotropicFiltering** pp3DAnisotropicFiltering) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetAnisotropicFiltering);
	}

	ADLX_RESULT  GetTessellation(IADLXGPU* pGPU, IADLX3DTessellation** pp3DTessellation) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetTessellation);
	}

	ADLX_RESULT  GetRadeonSuperResolution(IADLX3DRadeonSuperResolution** pp3DRadeonSuperResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetRadeonSuperResolution);
	}
	
	ADLX_RESULT  GetResetShaderCache(IADLXGPU* pGPU, IADLX3DResetShaderCache** pp3DResetShaderCache) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, GetResetShaderCache);
	}

	ADLX_RESULT  Get3DSettingsChangedHandling(IADLX3DSettingsChangedHandling** pp3DSettingsChangedHandling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices, Get3DSettingsChangedHandling);
	}
};

class Py3DSettingsServices1 : public IADLX3DSettingsServices1
{
public:
	using IADLX3DSettingsServices1::IADLX3DSettingsServices1;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  GetAntiLag(IADLXGPU* pGPU, IADLX3DAntiLag** pp3DAntiLag) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetAntiLag);
	}

	ADLX_RESULT  GetChill(IADLXGPU* pGPU, IADLX3DChill** pp3DChill) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetChill);
	}

	ADLX_RESULT  GetBoost(IADLXGPU* pGPU, IADLX3DBoost** pp3DBoost) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetBoost);
	}

	ADLX_RESULT  GetImageSharpening(IADLXGPU* pGPU, IADLX3DImageSharpening** pp3DImageSharpening) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetImageSharpening);
	}

	ADLX_RESULT  GetEnhancedSync(IADLXGPU* pGPU, IADLX3DEnhancedSync** pp3DEnhancedSync) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetEnhancedSync);
	}

	ADLX_RESULT  GetWaitForVerticalRefresh(IADLXGPU* pGPU, IADLX3DWaitForVerticalRefresh** pp3DWaitForVerticalRefresh) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetWaitForVerticalRefresh);
	}

	ADLX_RESULT  GetFrameRateTargetControl(IADLXGPU* pGPU, IADLX3DFrameRateTargetControl** pp3DFrameRateTargetControl) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetFrameRateTargetControl);
	}

	ADLX_RESULT  GetAntiAliasing(IADLXGPU* pGPU, IADLX3DAntiAliasing** pp3DAntiAliasing) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetAntiAliasing);
	}

	ADLX_RESULT  GetMorphologicalAntiAliasing(IADLXGPU* pGPU, IADLX3DMorphologicalAntiAliasing** pp3DMorphologicalAntiAliasing) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetMorphologicalAntiAliasing);
	}

	ADLX_RESULT  GetAnisotropicFiltering(IADLXGPU* pGPU, IADLX3DAnisotropicFiltering** pp3DAnisotropicFiltering) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetAnisotropicFiltering);
	}

	ADLX_RESULT  GetTessellation(IADLXGPU* pGPU, IADLX3DTessellation** pp3DTessellation) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetTessellation);
	}

	ADLX_RESULT  GetRadeonSuperResolution(IADLX3DRadeonSuperResolution** pp3DRadeonSuperResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetRadeonSuperResolution);
	}
	
	ADLX_RESULT  GetResetShaderCache(IADLXGPU* pGPU, IADLX3DResetShaderCache** pp3DResetShaderCache) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetResetShaderCache);
	}

	ADLX_RESULT  Get3DSettingsChangedHandling(IADLX3DSettingsChangedHandling** pp3DSettingsChangedHandling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, Get3DSettingsChangedHandling);
	}

	ADLX_RESULT  GetAMDFluidMotionFrames(IADLX3DAMDFluidMotionFrames** pp3DAMDFluidMotionFrames) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsServices1, GetAMDFluidMotionFrames);
	}
};

class PyDisplay : public IADLXDisplay
{
public:
	using IADLXDisplay::IADLXDisplay;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT ManufacturerID(adlx_uint* manufacturerID) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ManufacturerID);
	}

	ADLX_RESULT DisplayType(ADLX_DISPLAY_TYPE* displayType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, DisplayType);
	}

	ADLX_RESULT ConnectorType(ADLX_DISPLAY_CONNECTOR_TYPE* connectType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ConnectorType);
	}

	ADLX_RESULT Name(const char** displayName) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, Name);
	}

	ADLX_RESULT EDID(const char** edid) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, EDID);
	}

	ADLX_RESULT NativeResolution(adlx_int* maxHResolution, adlx_int* maxVResolution) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, NativeResolution);
	}

	ADLX_RESULT RefreshRate(adlx_double* refreshRate) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, RefreshRate);
	}

	ADLX_RESULT PixelClock(adlx_uint* pixelClock) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, PixelClock);
	}

	ADLX_RESULT ScanType(ADLX_DISPLAY_SCAN_TYPE* scanType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ScanType);
	}

	ADLX_RESULT GetGPU(IADLXGPU** ppGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, GetGPU);
	}

    ADLX_RESULT UniqueId(adlx_size* uniqueId) {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, UniqueId);
    }
};

class PyDisplayGPUScaling : public IADLXDisplayGPUScaling
{
public:
	using IADLXDisplayGPUScaling::IADLXDisplayGPUScaling;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGPUScaling, IsSupported);
	}

	ADLX_RESULT  IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGPUScaling, IsEnabled);
	}

	ADLX_RESULT  SetEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGPUScaling, SetEnabled);
	}
};

class PyDisplayScalingMode : public IADLXDisplayScalingMode
{
public:
	using IADLXDisplayScalingMode::IADLXDisplayScalingMode;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayScalingMode, IsSupported);
	}

	ADLX_RESULT  GetMode(ADLX_SCALE_MODE* currentMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayScalingMode, GetMode);
	}

	ADLX_RESULT  SetMode(ADLX_SCALE_MODE mode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayScalingMode, SetMode);
	}
};

class Py3DRadeonSuperResolution : public IADLX3DRadeonSuperResolution
{
public:
	using IADLX3DRadeonSuperResolution::IADLX3DRadeonSuperResolution;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, IsSupported);
	}

	ADLX_RESULT  IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, IsEnabled);
	}

	ADLX_RESULT  SetEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, SetEnabled);
	}

	ADLX_RESULT  GetSharpnessRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, GetSharpnessRange);
	}

	ADLX_RESULT  GetSharpness(adlx_int* currentSharpness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, GetSharpness);
	}

	ADLX_RESULT  SetSharpness(adlx_int sharpness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, SetSharpness);
	}
};

class Py3DAMDFluidMotionFrames : public IADLX3DAMDFluidMotionFrames
{
public:
	using IADLX3DAMDFluidMotionFrames::IADLX3DAMDFluidMotionFrames;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames, IsSupported);
	}

	ADLX_RESULT  IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames, IsEnabled);
	}

	ADLX_RESULT  SetEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAMDFluidMotionFrames, SetEnabled);
	}
};

class PyDisplayIntegerScaling : public IADLXDisplayIntegerScaling
{
public:
	using IADLXDisplayIntegerScaling::IADLXDisplayIntegerScaling;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT  IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayIntegerScaling, IsSupported);
	}

	ADLX_RESULT  IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayIntegerScaling, IsEnabled);
	}

	ADLX_RESULT  SetEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayIntegerScaling, SetEnabled);
	}
};

class PyDisplayChangeHandler : public IADLXDisplayChangedHandling
{
public:
	using IADLXDisplayChangedHandling::IADLXDisplayChangedHandling;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT AddDisplayListEventListener(IADLXDisplayListChangedListener *pDisplayListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayListEventListener);
	}

	ADLX_RESULT RemoveDisplayListEventListener(IADLXDisplayListChangedListener *pDisplayListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayListEventListener);
	}

	ADLX_RESULT AddDisplayGamutEventListener(IADLXDisplayGamutChangedListener *pDisplayGamutChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayGamutEventListener);
	}

	ADLX_RESULT RemoveDisplayGamutEventListener(IADLXDisplayGamutChangedListener *pDisplayGamutChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayGamutEventListener);
	}

	ADLX_RESULT AddDisplayGammaEventListener(IADLXDisplayGammaChangedListener *pDisplayGammaChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayGammaEventListener);
	}

	ADLX_RESULT RemoveDisplayGammaEventListener(IADLXDisplayGammaChangedListener *pDisplayGammaChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayGammaEventListener);
	}

	ADLX_RESULT AddDisplay3DLUTEventListener(IADLXDisplay3DLUTChangedListener *pDisplay3DLUTChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplay3DLUTEventListener);
	}

	ADLX_RESULT RemoveDisplay3DLUTEventListener(IADLXDisplay3DLUTChangedListener *pDisplay3DLUTChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplay3DLUTEventListener);
	}

    ADLX_RESULT AddDisplaySettingsEventListener(IADLXDisplaySettingsChangedListener* pDisplaySettingsChangedListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplaySettingsEventListener);
    }

    ADLX_RESULT RemoveDisplaySettingsEventListener(IADLXDisplaySettingsChangedListener* pDisplaySettingsChangedListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplaySettingsEventListener);
    }
};

// Callback
class DisplayListCallBack : public IADLXDisplayListChangedListener
{
public:

	adlx_bool OnDisplayListChanged(IADLXDisplayList *pNewDisplay) override {
		std::vector<IADLXDisplayPtr> list;
		for (adlx_uint s = pNewDisplay->Begin(); s != pNewDisplay->End(); s++) {
			IADLXDisplayPtr item;
			pNewDisplay->At(s, &item);
			list.emplace_back(item);
		}
		if (m_call) {
			return m_call(list);
		}
		return true;
	}

	std::function<bool(std::vector<IADLXDisplayPtr>)> m_call;
};

PYBIND11_MODULE(ADLXPybind, m) {

	m.doc() = "ADLX python binding for display & displayListChangedEvent";

	// Define the objects that get exposed to python
	// ADLX_RESULT
	py::enum_<ADLX_RESULT>(m, "ADLX_RESULT")
		.value("ADLX_OK", ADLX_RESULT::ADLX_OK)
		.value("ADLX_ALREADY_ENABLED", ADLX_RESULT::ADLX_ALREADY_ENABLED)
		.value("ADLX_ALREADY_INITIALIZED", ADLX_RESULT::ADLX_ALREADY_INITIALIZED)
		.value("ADLX_FAIL", ADLX_RESULT::ADLX_FAIL)
		.value("ADLX_INVALID_ARGS", ADLX_RESULT::ADLX_INVALID_ARGS)
		.value("ADLX_BAD_VER", ADLX_RESULT::ADLX_BAD_VER)
		.value("ADLX_UNKNOWN_INTERFACE", ADLX_RESULT::ADLX_UNKNOWN_INTERFACE)
		.value("ADLX_TERMINATED", ADLX_RESULT::ADLX_TERMINATED)
		.value("ADLX_ADL_INIT_ERROR", ADLX_RESULT::ADLX_ADL_INIT_ERROR)
		.value("ADLX_NOT_FOUND", ADLX_RESULT::ADLX_NOT_FOUND)
		.value("ADLX_INVALID_OBJECT", ADLX_RESULT::ADLX_INVALID_OBJECT)
		.value("ADLX_ORPHAN_OBJECTS", ADLX_RESULT::ADLX_ORPHAN_OBJECTS)
		.value("ADLX_NOT_SUPPORTED", ADLX_RESULT::ADLX_NOT_SUPPORTED)
		.export_values();

	// ADLX_DISPLAY_TYPE
	py::enum_<ADLX_DISPLAY_TYPE>(m, "ADLX_DISPLAY_TYPE")
		.value("DISPLAY_TYPE_UNKOWN", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_UNKOWN)
		.value("DISPLAY_TYPE_MONITOR", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_MONITOR)
		.value("DISPLAY_TYPE_TELEVISION", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_TELEVISION)
		.value("DISPLAY_TYPE_LCD_PANEL", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_LCD_PANEL)
		.value("DISPLAY_TYPE_DIGITAL_FLAT_PANEL", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_DIGITAL_FLAT_PANEL)
		.value("DISPLAY_TYPE_COMPONENT_VIDEO", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_COMPONENT_VIDEO)
		.value("DISPLAY_TYPE_PROJECTOR", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_PROJECTOR)
		.export_values();

	// ADLX_DISPLAY_CONNECTOR_TYPE
	py::enum_<ADLX_DISPLAY_CONNECTOR_TYPE>(m, "ADLX_DISPLAY_CONNECTOR_TYPE")
		.value("DISPLAY_CONTYPE_UNKNOWN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_UNKNOWN)
		.value("DISPLAY_CONTYPE_VGA", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_VGA)
		.value("DISPLAY_CONTYPE_DVI_D", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DVI_D)
		.value("DISPLAY_CONTYPE_DVI_I", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DVI_I)
		.value("DISPLAY_CONTYPE_CVDONGLE_NTSC", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NTSC)
		.value("DISPLAY_CONTYPE_CVDONGLE_JPN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_JPN)
		.value("DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN)
		.value("DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC)
		.value("DISPLAY_CONTYPE_HDMI_TYPE_A", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_HDMI_TYPE_A)
		.value("DISPLAY_CONTYPE_HDMI_TYPE_B", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_HDMI_TYPE_B)
		.value("DISPLAY_CONTYPE_SVIDEO", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_SVIDEO)
		.value("DISPLAY_CONTYPE_COMPOSITE", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_COMPOSITE)
		.value("DISPLAY_CONTYPE_RCA_3COMPONENT", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_RCA_3COMPONENT)
		.value("DISPLAY_CONTYPE_DISPLAYPORT", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DISPLAYPORT)
		.value("DISPLAY_CONTYPE_EDP", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_EDP)
		.value("DISPLAY_CONTYPE_WIRELESSDISPLAY", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_WIRELESSDISPLAY)
		.value("DISPLAY_CONTYPE_USB_TYPE_C", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_USB_TYPE_C)
		.export_values();

	// ADLX_DISPLAY_SCAN_TYPE
	py::enum_<ADLX_DISPLAY_SCAN_TYPE>(m, "ADLX_DISPLAY_SCAN_TYPE")
		.value("PROGRESSIVE", ADLX_DISPLAY_SCAN_TYPE::PROGRESSIVE)
		.value("INTERLACED", ADLX_DISPLAY_SCAN_TYPE::INTERLACED)
		.export_values();

	py::enum_<ADLX_SCALE_MODE>(m, "ADLX_SCALE_MODE")
		.value("PRESERVE_ASPECT_RATIO", ADLX_SCALE_MODE::PRESERVE_ASPECT_RATIO)
		.value("FULL_PANEL", ADLX_SCALE_MODE::FULL_PANEL)
		.value("CENTERED", ADLX_SCALE_MODE::CENTERED)
		.export_values();

	// ADLX_helper
	py::class_<ADLXHelper>(m, "ADLXHelper")
		.def(py::init<>())
		.def("InitializeWithCallerAdl", &ADLXHelper::InitializeWithCallerAdl)
		.def("Initialize", &ADLXHelper::Initialize)
		.def("InitializeWithIncompatibleDriver", &ADLXHelper::InitializeWithIncompatibleDriver)
		.def("Terminate", &ADLXHelper::Terminate)
		.def("QueryVersion", &ADLXHelper::QueryVersion)
		.def("GetSystemServices", &ADLXHelper::GetSystemServices, py::return_value_policy::reference)
		.def("GetAdlMapping", &ADLXHelper::GetAdlMapping);

	// System
	auto pyIADLXSystem = py::class_<IADLXSystem, PySystem>(m, "IADLXSystem");
	pyIADLXSystem.def(py::init<>())
		.def("GetDisplaysServices", [](py::object self) {
		IADLXSystem *sys = self.cast<IADLXSystem*>();
		IADLXDisplayServicesPtr displayService = nullptr;
		sys->GetDisplaysServices(&displayService);
		return displayService;
	}, py::return_value_policy::move);

	pyIADLXSystem.def(py::init<>())
		.def("Get3DSettingsServices", [](py::object self) {
		IADLXSystem* sys = self.cast<IADLXSystem*>();
		IADLX3DSettingsServicesPtr settingsServices = nullptr;
		sys->Get3DSettingsServices(&settingsServices);
		return settingsServices;
			}, py::return_value_policy::move);

	pyIADLXSystem.def(py::init<>())
		.def("Get3DSettingsServices1", [](py::object self) {
		IADLXSystem* sys = self.cast<IADLXSystem*>();
		IADLX3DSettingsServicesPtr settingsServices = nullptr;
		sys->Get3DSettingsServices(&settingsServices);
		return (IADLX3DSettingsServices1Ptr) settingsServices;
			}, py::return_value_policy::move);

	py::class_<IADLXDisplayGPUScaling, PyDisplayGPUScaling, IADLXInterfacePtr_T<IADLXDisplayGPUScaling>>(m, "IADLXDisplayGPUScaling")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLXDisplayGPUScaling* displayGPUScaling = self.cast<IADLXDisplayGPUScaling*>();
		adlx_bool isSupported = false;
		displayGPUScaling->IsSupported(&isSupported);
		return isSupported;
	})
		.def("IsEnabled", [](py::object self) {
		IADLXDisplayGPUScaling* displayGPUScaling = self.cast<IADLXDisplayGPUScaling*>();
		adlx_bool isEnabled = false;
		displayGPUScaling->IsEnabled(&isEnabled);
		return isEnabled;
	})
		.def("SetEnabled", [](py::object self, bool enable) {
		IADLXDisplayGPUScaling* displayGPUScaling = self.cast<IADLXDisplayGPUScaling*>();
		displayGPUScaling->SetEnabled(enable);
	});

	py::class_<IADLXDisplayScalingMode, PyDisplayScalingMode, IADLXInterfacePtr_T<IADLXDisplayScalingMode>>(m, "IADLXDisplayScalingMode")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLXDisplayScalingMode* displayScalingMode = self.cast<IADLXDisplayScalingMode*>();
		adlx_bool isSupported = false;
		displayScalingMode->IsSupported(&isSupported);
		return isSupported;
	})
		.def("GetMode", [](py::object self) {
		IADLXDisplayScalingMode* displayScalingMode = self.cast<IADLXDisplayScalingMode*>();
		ADLX_SCALE_MODE scaleMode;
		displayScalingMode->GetMode(&scaleMode);
		return scaleMode;
	})
		.def("SetMode", [](py::object self, ADLX_SCALE_MODE mode) {
		IADLXDisplayScalingMode* displayScalingMode = self.cast<IADLXDisplayScalingMode*>();
		displayScalingMode->SetMode(mode);
	});

	py::class_<IADLXDisplayIntegerScaling, PyDisplayIntegerScaling, IADLXInterfacePtr_T<IADLXDisplayIntegerScaling>>(m, "IADLXDisplayIntegerScaling")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLXDisplayIntegerScaling* displayIntegerScaling = self.cast<IADLXDisplayIntegerScaling*>();
		adlx_bool isSupported = false;
		displayIntegerScaling->IsSupported(&isSupported);
		return isSupported;
	})
		.def("IsEnabled", [](py::object self) {
		IADLXDisplayIntegerScaling* displayIntegerScaling = self.cast<IADLXDisplayIntegerScaling*>();
		adlx_bool isEnabled = false;
		displayIntegerScaling->IsEnabled(&isEnabled);
		return isEnabled;
	})
		.def("SetEnabled", [](py::object self, bool enable) {
		IADLXDisplayIntegerScaling* displayIntegerScaling = self.cast<IADLXDisplayIntegerScaling*>();
		displayIntegerScaling->SetEnabled(enable);
	});

	// displayService
	py::class_<IADLXDisplayServices, PyDisplayService, IADLXInterfacePtr_T<IADLXDisplayServices>>(m, "IADLXDisplayServices")
		.def(py::init<>())
		.def("GetNumberOfDisplays", [](py::object self) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		adlx_uint num;
		disService->GetNumberOfDisplays(&num);
		return num;
	})
		.def("GetDisplays", [](py::object self) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		IADLXDisplayListPtr displayList = nullptr;
		disService->GetDisplays(&displayList);
		std::vector<IADLXDisplayPtr> list;
		for (adlx_uint s = displayList->Begin(); s != displayList->End(); s++) {
			IADLXDisplayPtr item;
			displayList->At(s, &item);
			list.emplace_back(std::move(item));
		}
		return list;
	}, py::return_value_policy::move)
		.def("GetDisplayChangedHandling", [](py::object self) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		IADLXDisplayChangedHandlingPtr handler = nullptr;
		disService->GetDisplayChangedHandling(&handler);
		return handler;
	}, py::return_value_policy::move)
		.def("GetGPUScaling", [](py::object self, IADLXDisplayPtr display) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		IADLXDisplayGPUScalingPtr gpuScaling;
		disService->GetGPUScaling(display, &gpuScaling);
		return gpuScaling;
	})
		.def("GetScalingMode", [](py::object self, IADLXDisplayPtr display) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		IADLXDisplayScalingModePtr scalingMode;
		disService->GetScalingMode(display, &scalingMode);
		return scalingMode;
	})
		.def("GetIntegerScaling", [](py::object self, IADLXDisplayPtr display) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		IADLXDisplayIntegerScalingPtr integerScaling;
		disService->GetIntegerScaling(display, &integerScaling);
		return integerScaling;
	});

	py::class_<IADLXGPU, PyGPU, IADLXInterfacePtr_T<IADLXGPU>>(m, "IADLXGPU")
		.def(py::init<>())
		.def("vendorId", [](py::object self) {
		IADLXGPU* gpu = self.cast<IADLXGPU*>();
		const char* vendorId = nullptr;
		gpu->VendorId(&vendorId);
		return py::str(vendorId);
	})
		.def("name", [](py::object self) {
		IADLXGPU* gpu = self.cast<IADLXGPU*>();
		const char* name = nullptr;
		gpu->Name(&name);
		return py::str(name);
	});

	// Display
	py::class_<IADLXDisplay, PyDisplay, IADLXInterfacePtr_T<IADLXDisplay>>(m, "IADLXDisplay")
		.def(py::init<>())
		.def("name", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		const char *name = nullptr;
		display->Name(&name);
		return py::str(name);
	})
		.def("type", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		ADLX_DISPLAY_TYPE type;
		display->DisplayType(&type);
		return type;
	})
		.def("connectType", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		ADLX_DISPLAY_CONNECTOR_TYPE type;
		display->ConnectorType(&type);
		return type;
	})
		.def("ManufacturerID", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_uint id;
		display->ManufacturerID(&id);
		return id;
	})
		.def("EDID", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		const char* str = nullptr;
		display->EDID(&str);
		return std::string(str);
	})
		.def("resolution", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_int h, v;
		display->NativeResolution(&h, &v);
		return std::tuple<adlx_int, adlx_int>(h,v);
	})
		.def("RefreshRate", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_double value;
		display->RefreshRate(&value);
		return value;
	})
		.def("PixelClock", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_uint value;
		display->PixelClock(&value);
		return value;
	})
		.def("ScanType", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		ADLX_DISPLAY_SCAN_TYPE type;
		display->ScanType(&type);
		return type;
	})
        .def("UniqueId", [](py::object self) {
        IADLXDisplay *display = self.cast<IADLXDisplay*>();
        adlx_size id;
        display->UniqueId(&id);
        return id;
    })
		.def("GetGPU", [](py::object self) {
		IADLXDisplay* display = self.cast<IADLXDisplay*>();
		IADLXGPUPtr GPU;
		display->GetGPU(&GPU);
		return GPU;
	});

	// Display change handler
	py::class_<IADLXDisplayChangedHandling, PyDisplayChangeHandler, IADLXInterfacePtr_T<IADLXDisplayChangedHandling>>(m, "IADLXDisplayChangedHandling")
		.def(py::init<>())
		.def("AddDisplayListEventListener", [](py::object self, DisplayListCallBack* call) {
			IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
			return handler->AddDisplayListEventListener(call);
		})
		.def("RemoveDisplayListEventListener", [](py::object self, DisplayListCallBack* call) {
			IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
			return handler->RemoveDisplayListEventListener(call);
		});

	// Callback for displaylist
	py::class_<DisplayListCallBack>(m, "DisplayListCallBack")
		.def(py::init<>())
		.def_readwrite("call", &DisplayListCallBack::m_call);

	// 3D
	py::class_<IADLX3DAntiLag, Py3DAntiLag, IADLXInterfacePtr_T<IADLX3DAntiLag>>(m, "IADLX3DAntiLag")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLX3DAntiLag* antiLag = self.cast<IADLX3DAntiLag*>();
		adlx_bool isSupported = false;
		antiLag->IsSupported(&isSupported);
		return isSupported;
	})
		.def("IsEnabled", [](py::object self) {
		IADLX3DAntiLag* antiLag = self.cast<IADLX3DAntiLag*>();
		adlx_bool isEnabled = false;
		antiLag->IsEnabled(&isEnabled);
		return isEnabled;
	})
		.def("SetEnabled", [](py::object self, bool enable) {
		IADLX3DAntiLag* antiLag = self.cast<IADLX3DAntiLag*>();
		antiLag->SetEnabled(enable);
	});

	py::class_<IADLX3DChill, Py3DChill, IADLXInterfacePtr_T<IADLX3DChill>>(m, "IADLX3DChill")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLX3DChill* chill = self.cast<IADLX3DChill*>();
		adlx_bool isSupported = false;
		chill->IsSupported(&isSupported);
		return isSupported;
	})
		.def("IsEnabled", [](py::object self) {
		IADLX3DChill* chill = self.cast<IADLX3DChill*>();
		adlx_bool isEnabled = false;
		chill->IsEnabled(&isEnabled);
		return isEnabled;
	})
		.def("SetEnabled", [](py::object self, bool enable) {
		IADLX3DChill* chill = self.cast<IADLX3DChill*>();
		chill->SetEnabled(enable);
	})
		.def("GetMinFPS", [](py::object self) {
		IADLX3DChill* chill = self.cast<IADLX3DChill*>();
		adlx_int minFPS;
		chill->GetMinFPS(&minFPS);
		return minFPS;
	})
		.def("GetMaxFPS", [](py::object self) {
		IADLX3DChill* chill = self.cast<IADLX3DChill*>();
		adlx_int maxFPS;
		chill->GetMaxFPS(&maxFPS);
		return maxFPS;
	})
		.def("SetMinFPS", [](py::object self, int minFPS) {
		IADLX3DChill* chill = self.cast<IADLX3DChill*>();
		chill->SetMinFPS(minFPS);
	})
		.def("SetMaxFPS", [](py::object self, int maxFPS) {
		IADLX3DChill* chill = self.cast<IADLX3DChill*>();
		chill->SetMaxFPS(maxFPS);
	});

	py::class_<IADLX3DBoost, Py3DBoost, IADLXInterfacePtr_T<IADLX3DBoost>>(m, "IADLX3DBoost")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLX3DBoost* boost = self.cast<IADLX3DBoost*>();
		adlx_bool isSupported = false;
		boost->IsSupported(&isSupported);
		return isSupported;
	})
		.def("IsEnabled", [](py::object self) {
		IADLX3DBoost* boost = self.cast<IADLX3DBoost*>();
		adlx_bool isEnabled = false;
		boost->IsEnabled(&isEnabled);
		return isEnabled;
	})
		.def("SetEnabled", [](py::object self, bool enable) {
		IADLX3DBoost* boost = self.cast<IADLX3DBoost*>();
		boost->SetEnabled(enable);
	})
		.def("GetResolutionRange", [](py::object self) {
		IADLX3DBoost* boost = self.cast<IADLX3DBoost*>();
		ADLX_IntRange resolutionRange;
		boost->GetResolutionRange(&resolutionRange);
		return resolutionRange;
	})
		.def("GetResolution", [](py::object self) {
		IADLX3DBoost* boost = self.cast<IADLX3DBoost*>();
		adlx_int resolution;
		boost->GetResolution(&resolution);
		return resolution;
	})
	.def("SetResolution", [](py::object self, int resolution) {
		IADLX3DBoost* boost = self.cast<IADLX3DBoost*>();
		boost->SetResolution(resolution);
	});

	py::class_<IADLX3DRadeonSuperResolution, Py3DRadeonSuperResolution, IADLXInterfacePtr_T<IADLX3DRadeonSuperResolution>>(m, "IADLX3DRadeonSuperResolution")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLX3DRadeonSuperResolution* radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
		adlx_bool isSupported = false;
		radeonSuperResolution->IsSupported(&isSupported);
		return isSupported;
	})
		.def("IsEnabled", [](py::object self) {
		IADLX3DRadeonSuperResolution* radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
		adlx_bool isEnabled = false;
		radeonSuperResolution->IsEnabled(&isEnabled);
		return isEnabled;
	})
		.def("SetEnabled", [](py::object self, bool enable) {
		IADLX3DRadeonSuperResolution* radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
		radeonSuperResolution->SetEnabled(enable);
	})
		.def("GetSharpnessRange", [](py::object self) {
		IADLX3DRadeonSuperResolution* radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
		ADLX_IntRange sharpnessRange;
		radeonSuperResolution->GetSharpnessRange(&sharpnessRange);
		return sharpnessRange;
	})
		.def("GetSharpness", [](py::object self) {
		IADLX3DRadeonSuperResolution* radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
		adlx_int sharpness;
		radeonSuperResolution->GetSharpness(&sharpness);
		return sharpness;
	})
	.def("SetSharpness", [](py::object self, int sharpness) {
		IADLX3DRadeonSuperResolution* radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
		radeonSuperResolution->SetSharpness(sharpness);
	});

	py::class_<IADLX3DAMDFluidMotionFrames, Py3DAMDFluidMotionFrames, IADLXInterfacePtr_T<IADLX3DAMDFluidMotionFrames>>(m, "IADLX3DAMDFluidMotionFrames")
		.def(py::init<>())
		.def("IsSupported", [](py::object self) {
		IADLX3DAMDFluidMotionFrames* amdFluidMotionFrame = self.cast<IADLX3DAMDFluidMotionFrames*>();
		adlx_bool isSupported = false;
		amdFluidMotionFrame->IsSupported(&isSupported);
		return isSupported;
	})
		.def("IsEnabled", [](py::object self) {
		IADLX3DAMDFluidMotionFrames* amdFluidMotionFrame = self.cast<IADLX3DAMDFluidMotionFrames*>();
		adlx_bool isEnabled = false;
		amdFluidMotionFrame->IsEnabled(&isEnabled);
		return isEnabled;
	})
		.def("SetEnabled", [](py::object self, bool enable) {
		IADLX3DAMDFluidMotionFrames* amdFluidMotionFrame = self.cast<IADLX3DAMDFluidMotionFrames*>();
		amdFluidMotionFrame->SetEnabled(enable);
	});

	py::class_<IADLX3DSettingsServices, Py3DSettingsServices, IADLXInterfacePtr_T<IADLX3DSettingsServices>>(m, "IADLX3DSettingsServices")
		.def(py::init<>())
		.def("GetAntiLag", [](py::object self, IADLXGPUPtr gpu) {
		IADLX3DSettingsServices* settingsServices = self.cast<IADLX3DSettingsServices*>();
		IADLX3DAntiLagPtr antiLag;
		settingsServices->GetAntiLag(gpu, &antiLag);
		return antiLag;
	})
		.def("GetChill", [](py::object self, IADLXGPUPtr gpu) {
		IADLX3DSettingsServices* settingsServices = self.cast<IADLX3DSettingsServices*>();
		IADLX3DChillPtr chill;
		settingsServices->GetChill(gpu, &chill);
		return chill;
	})
		.def("GetBoost", [](py::object self, IADLXGPUPtr gpu) {
		IADLX3DSettingsServices* settingsServices = self.cast<IADLX3DSettingsServices*>();
		IADLX3DBoostPtr boost;
		settingsServices->GetBoost(gpu, &boost);
		return boost;
	})
		.def("GetRadeonSuperResolution", [](py::object self) {
		IADLX3DSettingsServices* settingsServices = self.cast<IADLX3DSettingsServices*>();
		IADLX3DRadeonSuperResolutionPtr radeonSuperResolution;
		settingsServices->GetRadeonSuperResolution(&radeonSuperResolution);
		return radeonSuperResolution;
	});

	py::class_<IADLX3DSettingsServices1, Py3DSettingsServices1, IADLXInterfacePtr_T<IADLX3DSettingsServices1>>(m, "IADLX3DSettingsServices1")
		.def(py::init<>())
		.def("GetAMDFluidMotionFrame", [](py::object self) {
		IADLX3DSettingsServices1* settingsServices1 = self.cast<IADLX3DSettingsServices1*>();
		IADLX3DAMDFluidMotionFramesPtr amdFluidMotionFrame;
		settingsServices1->GetAMDFluidMotionFrames(&amdFluidMotionFrame);
		return amdFluidMotionFrame;
	});
}
