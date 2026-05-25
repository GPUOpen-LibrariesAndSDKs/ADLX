//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// IADLXGPU and IADLXGPUList (see SDK/Include/ISystem.h)
// -------------------------------------------------------------------------------------------------
// ADLX_GPU_TYPE values.
pub const GPUTYPE_UNDEFINED: c_int = 0;
pub const GPUTYPE_INTEGRATED: c_int = 1;
pub const GPUTYPE_DISCRETE: c_int = 2;

#[repr(C)]
pub struct IADLXGPUVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPU) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPU) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub VendorId: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        vendorId: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub ASICFamilyType:
        unsafe extern "system" fn(pThis: *mut IADLXGPU, asicFamilyType: *mut c_int) -> ADLX_RESULT,
    pub Type: unsafe extern "system" fn(pThis: *mut IADLXGPU, gpuType: *mut c_int) -> ADLX_RESULT,
    pub IsExternal:
        unsafe extern "system" fn(pThis: *mut IADLXGPU, isExternal: *mut adlx_bool) -> ADLX_RESULT,
    pub Name:
        unsafe extern "system" fn(pThis: *mut IADLXGPU, gpuName: *mut *const c_char) -> ADLX_RESULT,
    pub DriverPath: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        driverPath: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub PNPString: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        pnpString: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub HasDesktops:
        unsafe extern "system" fn(pThis: *mut IADLXGPU, hasDesktops: *mut adlx_bool) -> ADLX_RESULT,
    pub TotalVRAM:
        unsafe extern "system" fn(pThis: *mut IADLXGPU, vramMB: *mut adlx_uint) -> ADLX_RESULT,
    pub VRAMType: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        vramType: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub BIOSInfo: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        partNumber: *mut *const c_char,
        version: *mut *const c_char,
        date: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub DeviceId: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        deviceId: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub RevisionId: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        revisionId: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub SubSystemId: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        subSystemId: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub SubSystemVendorId: unsafe extern "system" fn(
        pThis: *mut IADLXGPU,
        subSystemVendorId: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub UniqueId:
        unsafe extern "system" fn(pThis: *mut IADLXGPU, uniqueId: *mut adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPU {
    pub pVtbl: *const IADLXGPUVtbl,
}

#[repr(C)]
pub struct IADLXGPUListVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUList,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Size: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> adlx_uint,
    pub Empty: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> adlx_bool,
    pub Begin: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> adlx_uint,
    pub End: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> adlx_uint,
    pub At: unsafe extern "system" fn(
        pThis: *mut IADLXGPUList,
        location: adlx_uint,
        ppItem: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub Clear: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> ADLX_RESULT,
    pub Remove_Back: unsafe extern "system" fn(pThis: *mut IADLXGPUList) -> ADLX_RESULT,
    pub Add_Back: unsafe extern "system" fn(
        pThis: *mut IADLXGPUList,
        pItem: *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub At_GPUList: unsafe extern "system" fn(
        pThis: *mut IADLXGPUList,
        location: adlx_uint,
        ppItem: *mut *mut IADLXGPU,
    ) -> ADLX_RESULT,
    pub Add_Back_GPUList:
        unsafe extern "system" fn(pThis: *mut IADLXGPUList, pItem: *mut IADLXGPU) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUList {
    pub pVtbl: *const IADLXGPUListVtbl,
}

/// `IADLXGPU3` (see SDK/Include/ISystem3.h). Obtain it by calling `QueryInterface`
/// on an `IADLXGPU` with the id `"IADLXGPU3"`. A prefix of the interface is declared
/// here, up to and including the GPU stress-test methods used by the sample. Enum
/// and struct out-params that are not read by the samples use `c_int`/`*mut c_void`
/// so that the vtable layout (and therefore the method offsets) stays correct.
#[repr(C)]
pub struct IADLXGPU3Vtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPU3) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPU3) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub VendorId:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, vendorId: *mut *const c_char) -> ADLX_RESULT,
    pub ASICFamilyType:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, asicFamilyType: *mut c_int) -> ADLX_RESULT,
    pub Type: unsafe extern "system" fn(pThis: *mut IADLXGPU3, gpuType: *mut c_int) -> ADLX_RESULT,
    pub IsExternal:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, isExternal: *mut adlx_bool) -> ADLX_RESULT,
    pub Name:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, gpuName: *mut *const c_char) -> ADLX_RESULT,
    pub DriverPath:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, driverPath: *mut *const c_char) -> ADLX_RESULT,
    pub PNPString:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, pnpString: *mut *const c_char) -> ADLX_RESULT,
    pub HasDesktops:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, hasDesktops: *mut adlx_bool) -> ADLX_RESULT,
    pub TotalVRAM:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, vramMB: *mut adlx_uint) -> ADLX_RESULT,
    pub VRAMType:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, vramType: *mut *const c_char) -> ADLX_RESULT,
    pub BIOSInfo: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        partNumber: *mut *const c_char,
        version: *mut *const c_char,
        date: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub DeviceId:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, deviceId: *mut *const c_char) -> ADLX_RESULT,
    pub RevisionId:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, revisionId: *mut *const c_char) -> ADLX_RESULT,
    pub SubSystemId:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, subSystemId: *mut *const c_char) -> ADLX_RESULT,
    pub SubSystemVendorId: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        subSystemVendorId: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub UniqueId:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, uniqueId: *mut adlx_int) -> ADLX_RESULT,
    pub PCIBusType:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, busType: *mut c_int) -> ADLX_RESULT,
    pub PCIBusLaneWidth:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, laneWidth: *mut adlx_uint) -> ADLX_RESULT,
    pub MultiGPUMode:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, mode: *mut c_int) -> ADLX_RESULT,
    pub ProductName:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, productName: *mut *const c_char) -> ADLX_RESULT,
    pub IsPowerOff:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, state: *mut adlx_bool) -> ADLX_RESULT,
    pub PowerOn: unsafe extern "system" fn(pThis: *mut IADLXGPU3) -> ADLX_RESULT,
    pub StartPowerOff: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        pGPUConnectChangedListener: *mut c_void,
        timeout: adlx_int,
    ) -> ADLX_RESULT,
    pub AbortPowerOff: unsafe extern "system" fn(pThis: *mut IADLXGPU3) -> ADLX_RESULT,
    pub IsSupportedApplicationList:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub GetApplications: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        ppApplications: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub AMDSoftwareReleaseDate: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        year: *mut adlx_uint,
        month: *mut adlx_uint,
        day: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub AMDSoftwareEdition:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, edition: *mut *const c_char) -> ADLX_RESULT,
    pub AMDSoftwareVersion:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, version: *mut *const c_char) -> ADLX_RESULT,
    pub DriverVersion:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, version: *mut *const c_char) -> ADLX_RESULT,
    pub AMDWindowsDriverVersion:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, version: *mut *const c_char) -> ADLX_RESULT,
    pub LUID: unsafe extern "system" fn(pThis: *mut IADLXGPU3, luid: *mut c_void) -> ADLX_RESULT,
    pub MicroArchitecture: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        microArchitecture: *mut *const c_char,
    ) -> ADLX_RESULT,
    pub HighestVRAMBandwidth:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, data: *mut adlx_uint) -> ADLX_RESULT,
    pub InvisibleVRAM:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, data: *mut adlx_uint) -> ADLX_RESULT,
    pub VisibleVRAM:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, data: *mut adlx_uint) -> ADLX_RESULT,
    pub VRAMVendorRevId:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, data: *mut adlx_uint) -> ADLX_RESULT,
    pub VRAMBandwidth:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, data: *mut adlx_uint) -> ADLX_RESULT,
    pub VRAMBitRate:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, data: *mut adlx_uint) -> ADLX_RESULT,
    pub IsSupportedStressTest:
        unsafe extern "system" fn(pThis: *mut IADLXGPU3, supported: *mut adlx_bool) -> ADLX_RESULT,
    pub StartStressTest: unsafe extern "system" fn(
        pThis: *mut IADLXGPU3,
        pGPUStressTestFinishedListener: *mut IADLXGPUStressTestFinishedListener,
        time: adlx_uint,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPU3 {
    pub pVtbl: *const IADLXGPU3Vtbl,
}

// -------------------------------------------------------------------------------------------------
