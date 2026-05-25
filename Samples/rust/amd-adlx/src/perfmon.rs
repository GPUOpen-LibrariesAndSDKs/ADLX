//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// Performance monitoring (see SDK/Include/IPerformanceMonitoring.h)
// -------------------------------------------------------------------------------------------------
/// `ADLX_IntRange` (see SDK/Include/ADLXStructures.h).
#[repr(C)]
pub struct ADLX_IntRange {
    pub minValue: adlx_int,
    pub maxValue: adlx_int,
    pub step: adlx_int,
}

#[repr(C)]
pub struct IADLXPerformanceMonitoringServicesVtbl {
    pub Acquire:
        unsafe extern "system" fn(pThis: *mut IADLXPerformanceMonitoringServices) -> adlx_long,
    pub Release:
        unsafe extern "system" fn(pThis: *mut IADLXPerformanceMonitoringServices) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetSamplingIntervalRange: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub SetSamplingInterval: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        intervalMs: adlx_int,
    ) -> ADLX_RESULT,
    pub GetSamplingInterval: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        intervalMs: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetMaxPerformanceMetricsHistorySizeRange: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        range: *mut ADLX_IntRange,
    ) -> ADLX_RESULT,
    pub SetMaxPerformanceMetricsHistorySize: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        sizeSec: adlx_int,
    ) -> ADLX_RESULT,
    pub GetMaxPerformanceMetricsHistorySize: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        sizeSec: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub ClearPerformanceMetricsHistory:
        unsafe extern "system" fn(pThis: *mut IADLXPerformanceMonitoringServices) -> ADLX_RESULT,
    pub GetCurrentPerformanceMetricsHistorySize: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        sizeSec: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub StartPerformanceMetricsTracking:
        unsafe extern "system" fn(pThis: *mut IADLXPerformanceMonitoringServices) -> ADLX_RESULT,
    pub StopPerformanceMetricsTracking:
        unsafe extern "system" fn(pThis: *mut IADLXPerformanceMonitoringServices) -> ADLX_RESULT,
    pub GetAllMetricsHistory: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        startMs: adlx_int,
        stopMs: adlx_int,
        ppMetricsList: *mut *mut IADLXAllMetricsList,
    ) -> ADLX_RESULT,
    pub GetGPUMetricsHistory: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        pGPU: *mut IADLXGPU,
        startMs: adlx_int,
        stopMs: adlx_int,
        ppMetricsList: *mut *mut IADLXGPUMetricsList,
    ) -> ADLX_RESULT,
    pub GetSystemMetricsHistory: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        startMs: adlx_int,
        stopMs: adlx_int,
        ppMetricsList: *mut *mut IADLXSystemMetricsList,
    ) -> ADLX_RESULT,
    pub GetFPSHistory: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        startMs: adlx_int,
        stopMs: adlx_int,
        ppMetricsList: *mut *mut IADLXFPSList,
    ) -> ADLX_RESULT,
    pub GetCurrentAllMetrics: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        ppMetrics: *mut *mut IADLXAllMetrics,
    ) -> ADLX_RESULT,
    pub GetCurrentGPUMetrics: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        pGPU: *mut IADLXGPU,
        ppMetrics: *mut *mut IADLXGPUMetrics,
    ) -> ADLX_RESULT,
    pub GetCurrentSystemMetrics: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        ppMetrics: *mut *mut IADLXSystemMetrics,
    ) -> ADLX_RESULT,
    pub GetCurrentFPS: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        ppMetrics: *mut *mut IADLXFPS,
    ) -> ADLX_RESULT,
    pub GetSupportedGPUMetrics: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        pGPU: *mut IADLXGPU,
        ppMetricsSupported: *mut *mut IADLXGPUMetricsSupport,
    ) -> ADLX_RESULT,
    pub GetSupportedSystemMetrics: unsafe extern "system" fn(
        pThis: *mut IADLXPerformanceMonitoringServices,
        ppMetricsSupported: *mut *mut IADLXSystemMetricsSupport,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXPerformanceMonitoringServices {
    pub pVtbl: *const IADLXPerformanceMonitoringServicesVtbl,
}

#[repr(C)]
pub struct IADLXGPUMetricsSupportVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUMetricsSupport) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUMetricsSupport) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUUsage: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUClockSpeed: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUVRAMClockSpeed: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUTemperature: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUHotspotTemperature: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUPower: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUTotalBoardPower: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUFanSpeed: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUVRAM: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUVoltage: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetGPUUsageRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUClockSpeedRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUVRAMClockSpeedRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUTemperatureRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUHotspotTemperatureRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUPowerRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUFanSpeedRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUVRAMRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUVoltageRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUTotalBoardPowerRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetGPUIntakeTemperatureRange: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub IsSupportedGPUIntakeTemperature: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUMetricsSupport {
    pub pVtbl: *const IADLXGPUMetricsSupportVtbl,
}

#[repr(C)]
pub struct IADLXGPUMetricsVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetrics,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub TimeStamp:
        unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics, ms: *mut adlx_int64) -> ADLX_RESULT,
    pub GPUUsage: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetrics,
        data: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub GPUClockSpeed:
        unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics, data: *mut adlx_int) -> ADLX_RESULT,
    pub GPUVRAMClockSpeed:
        unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics, data: *mut adlx_int) -> ADLX_RESULT,
    pub GPUTemperature: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetrics,
        data: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub GPUHotspotTemperature: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetrics,
        data: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub GPUPower: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetrics,
        data: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub GPUTotalBoardPower: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetrics,
        data: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub GPUFanSpeed:
        unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics, data: *mut adlx_int) -> ADLX_RESULT,
    pub GPUVRAM:
        unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics, data: *mut adlx_int) -> ADLX_RESULT,
    pub GPUVoltage:
        unsafe extern "system" fn(pThis: *mut IADLXGPUMetrics, data: *mut adlx_int) -> ADLX_RESULT,
    pub GPUIntakeTemperature: unsafe extern "system" fn(
        pThis: *mut IADLXGPUMetrics,
        data: *mut adlx_double,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXGPUMetrics {
    pub pVtbl: *const IADLXGPUMetricsVtbl,
}

#[repr(C)]
pub struct IADLXSystemMetricsSupportVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSystemMetricsSupport) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSystemMetricsSupport) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetricsSupport,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub IsSupportedCPUUsage: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedSystemRAM: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub IsSupportedSmartShift: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetricsSupport,
        supported: *mut adlx_bool,
    ) -> ADLX_RESULT,
    pub GetCPUUsageRange: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetSystemRAMRange: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub GetSmartShiftRange: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetricsSupport,
        minValue: *mut adlx_int,
        maxValue: *mut adlx_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSystemMetricsSupport {
    pub pVtbl: *const IADLXSystemMetricsSupportVtbl,
}

#[repr(C)]
pub struct IADLXSystemMetricsVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXSystemMetrics) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXSystemMetrics) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetrics,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub TimeStamp: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetrics,
        ms: *mut adlx_int64,
    ) -> ADLX_RESULT,
    pub CPUUsage: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetrics,
        data: *mut adlx_double,
    ) -> ADLX_RESULT,
    pub SystemRAM: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetrics,
        data: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub SmartShift: unsafe extern "system" fn(
        pThis: *mut IADLXSystemMetrics,
        data: *mut adlx_int,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXSystemMetrics {
    pub pVtbl: *const IADLXSystemMetricsVtbl,
}

#[repr(C)]
pub struct IADLXFPSVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXFPS) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXFPS) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXFPS,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub TimeStamp:
        unsafe extern "system" fn(pThis: *mut IADLXFPS, ms: *mut adlx_int64) -> ADLX_RESULT,
    pub FPS: unsafe extern "system" fn(pThis: *mut IADLXFPS, data: *mut adlx_int) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXFPS {
    pub pVtbl: *const IADLXFPSVtbl,
}

// -------------------------------------------------------------------------------------------------
