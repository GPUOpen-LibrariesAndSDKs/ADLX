// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring.h"


namespace py = pybind11;
using namespace adlx;


class PyPerformanceMonitoringServices : IADLXPerformanceMonitoringServices
{
public:
	using IADLXPerformanceMonitoringServices::IADLXPerformanceMonitoringServices;

	ADLX_RESULT GetSamplingIntervalRange (ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSamplingIntervalRange);
	}

	ADLX_RESULT SetSamplingInterval (adlx_int askedIntervalMs) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, SetSamplingInterval);
	}

	ADLX_RESULT GetSamplingInterval (adlx_int* intervalMs) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSamplingInterval);
	}

	ADLX_RESULT GetMaxPerformanceMetricsHistorySizeRange (ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetMaxPerformanceMetricsHistorySizeRange);
	}

	ADLX_RESULT SetMaxPerformanceMetricsHistorySize (adlx_int sizeSec) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, SetMaxPerformanceMetricsHistorySize);
	}

	ADLX_RESULT GetMaxPerformanceMetricsHistorySize (adlx_int* sizeSec) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetMaxPerformanceMetricsHistorySize);
	}

	ADLX_RESULT ClearPerformanceMetricsHistory () override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, ClearPerformanceMetricsHistory);
	}

	ADLX_RESULT GetCurrentPerformanceMetricsHistorySize (adlx_int* sizeSec) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentPerformanceMetricsHistorySize);
	}

	ADLX_RESULT StartPerformanceMetricsTracking () override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, StartPerformanceMetricsTracking);
	}

	ADLX_RESULT StopPerformanceMetricsTracking () override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, StopPerformanceMetricsTracking);
	}

	ADLX_RESULT GetSupportedSystemMetrics(IADLXSystemMetricsSupport** ppMetricsSupported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSupportedSystemMetrics);
	}

	ADLX_RESULT GetCurrentSystemMetrics(IADLXSystemMetrics** ppMetrics) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentSystemMetrics);
	}

	ADLX_RESULT GetCurrentFPS(IADLXFPS** ppMetrics) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentFPS);
	}

	ADLX_RESULT GetCurrentAllMetrics(IADLXAllMetrics** ppMetrics) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentAllMetrics);
	}

	ADLX_RESULT GetSupportedGPUMetrics(IADLXGPU* pGPU, IADLXGPUMetricsSupport** ppMetricsSupported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSupportedGPUMetrics);
	}

	ADLX_RESULT GetCurrentGPUMetrics(IADLXGPU* pGPU, IADLXGPUMetrics** ppMetrics) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetCurrentGPUMetrics);
	}

	ADLX_RESULT GetAllMetricsHistory (adlx_int startMs, adlx_int stopMs, IADLXAllMetricsList** ppMetricsList) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetAllMetricsHistory);
	}

	ADLX_RESULT GetFPSHistory (adlx_int startMs, adlx_int stopMs, IADLXFPSList** ppMetricsList) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetFPSHistory);
	}

	ADLX_RESULT GetGPUMetricsHistory (IADLXGPU* pGPU, adlx_int startMs, adlx_int stopMs, IADLXGPUMetricsList** ppMetricsList) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetGPUMetricsHistory);
	}

	ADLX_RESULT GetSystemMetricsHistory (adlx_int startMs, adlx_int stopMs, IADLXSystemMetricsList** ppMetricsList) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXPerformanceMonitoringServices, GetSystemMetricsHistory);
	}

};
