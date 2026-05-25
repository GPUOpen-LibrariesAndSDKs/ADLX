//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_performance(py::module_& m)
{
    // PerfMonitoring
    py::class_<IADLXPerformanceMonitoringServices, IADLXInterface, PyPerformanceMonitoringServices, IADLXInterfacePtr_T<IADLXPerformanceMonitoringServices>>(m, "IADLXPerformanceMonitoringServices")
        //.def(py::init<>())
        .def("GetSamplingIntervalRange", [] (py::object self) -> std::variant<ADLX_IntRange, py::none> {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        ADLX_IntRange range;
        ADLX_RESULT ret = perfMetrics->GetSamplingIntervalRange(&range);
        if (ADLX_SUCCEEDED(ret))
            return range;
        return py::none();
        })
        .def("SetSamplingInterval", [] (py::object self, adlx_int askedIntervalMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        ADLX_RESULT retSetSamplingInterval = perfMetrics->SetSamplingInterval(askedIntervalMs);
        return retSetSamplingInterval;
        })
        .def("GetSamplingInterval", [] (py::object self) -> std::variant<adlx_int, py::none> {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        adlx_int intervalMs;
        ADLX_RESULT ret = perfMetrics->GetSamplingInterval(&intervalMs);
        if (ADLX_SUCCEEDED(ret))
            return intervalMs;
        return py::none();
        })
        .def("GetMaxPerformanceMetricsHistorySizeRange", [] (py::object self) -> std::variant<ADLX_IntRange, py::none> {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        ADLX_IntRange range;
        ADLX_RESULT ret = perfMetrics->GetMaxPerformanceMetricsHistorySizeRange(&range);
        if (ADLX_SUCCEEDED(ret))
            return range;
        return py::none();
        })
        .def("SetMaxPerformanceMetricsHistorySize", [] (py::object self, adlx_int sizeSec) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        ADLX_RESULT retSetMaxHistorySize = perfMetrics->SetMaxPerformanceMetricsHistorySize(sizeSec);
        return retSetMaxHistorySize;
        })
        .def("GetMaxPerformanceMetricsHistorySize", [] (py::object self) -> std::variant<adlx_int, py::none> {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        adlx_int sizeSec;
        ADLX_RESULT ret = perfMetrics->GetMaxPerformanceMetricsHistorySize(&sizeSec);
        if (ADLX_SUCCEEDED(ret))
            return sizeSec;
        return py::none();
        })
        .def("ClearPerformanceMetricsHistory", [] (py::object self) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        ADLX_RESULT retClearHistory = perfMetrics->ClearPerformanceMetricsHistory();
        return retClearHistory;
        })
        .def("GetCurrentPerformanceMetricsHistorySize", [] (py::object self) -> std::variant<adlx_int, py::none> {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        adlx_int sizeSec;
        ADLX_RESULT ret = perfMetrics->GetCurrentPerformanceMetricsHistorySize(&sizeSec);
        if (ADLX_SUCCEEDED(ret))
            return sizeSec;
        return py::none();
        })
        .def("StartPerformanceMetricsTracking", [] (py::object self) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        ADLX_RESULT retStartPerformanceMetricsTracking = perfMetrics->StartPerformanceMetricsTracking();
        return retStartPerformanceMetricsTracking;
        })
        .def("StopPerformanceMetricsTracking", [] (py::object self) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        ADLX_RESULT retStopPerformanceMetricsTracking = perfMetrics->StopPerformanceMetricsTracking();
        return retStopPerformanceMetricsTracking;
        })
        .def("GetSupportedSystemMetrics", [](py::object self) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXSystemMetricsSupportPtr sysMetricSuprt;
        perfMetrics->GetSupportedSystemMetrics(&sysMetricSuprt);
        return sysMetricSuprt;
        }, py::return_value_policy::move)
        .def("GetCurrentSystemMetrics", [](py::object self) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXSystemMetricsPtr sysMetric;
        perfMetrics->GetCurrentSystemMetrics(&sysMetric);
        return sysMetric;
        }, py::return_value_policy::move)
        .def("GetCurrentFPS", [](py::object self) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXFPSPtr ppMetrics;
        perfMetrics->GetCurrentFPS(&ppMetrics);
        return ppMetrics;
        }, py::return_value_policy::move)
        .def("GetCurrentAllMetrics", [](py::object self) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXAllMetricsPtr ppMetrics;
        perfMetrics->GetCurrentAllMetrics(&ppMetrics);
        return ppMetrics;
        }, py::return_value_policy::move)
        .def("GetSupportedGPUMetrics", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXGPUMetricsSupportPtr gpuMetricSuprt;
        perfMetrics->GetSupportedGPUMetrics(oneGPU, &gpuMetricSuprt);
        return gpuMetricSuprt;
        }, py::return_value_policy::move)
        .def("GetCurrentGPUMetrics", [](py::object self, IADLXGPU* pGPU) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXGPUMetricsPtr gpuMetrics;
        perfMetrics->GetCurrentGPUMetrics(pGPU, &gpuMetrics);
        return gpuMetrics;
        }, py::return_value_policy::move)
        .def("GetAllMetricsHistory", [](py::object self, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXAllMetricsListPtr allMetricsList;
        perfMetrics->GetAllMetricsHistory(startMs, stopMs, &allMetricsList);
        std::vector<IADLXAllMetricsPtr> list;
        if (allMetricsList)
        {
            for (adlx_uint s = allMetricsList->Begin(); s != allMetricsList->End(); s++) {
                IADLXAllMetricsPtr item;
                allMetricsList->At(s, &item);
                list.emplace_back(std::move(item));
            }
        }
        return list;
        }, py::return_value_policy::move)
        .def("GetFPSHistory", [](py::object self, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXFPSListPtr fpsList;
        perfMetrics->GetFPSHistory(startMs, stopMs, &fpsList);
        std::vector<IADLXFPSPtr> list;
        if (fpsList)
        {
            for (adlx_uint s = fpsList->Begin(); s != fpsList->End(); s++) {
                IADLXFPSPtr item;
                fpsList->At(s, &item);
                list.emplace_back(std::move(item));
            }
        }
        return list;
        }, py::return_value_policy::move)
        .def("GetGPUMetricsHistory", [](py::object self, IADLXGPUPtr oneGPU, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXGPUMetricsListPtr gpuMetricsList;
        perfMetrics->GetGPUMetricsHistory(oneGPU, startMs, stopMs, &gpuMetricsList);
        std::vector<IADLXGPUMetricsPtr> list;
        if (gpuMetricsList)
        {
            for (adlx_uint s = gpuMetricsList->Begin(); s != gpuMetricsList->End(); s++) {
                IADLXGPUMetricsPtr item;
                gpuMetricsList->At(s, &item);
                list.emplace_back(std::move(item));
            }
        }
        return list;
        }, py::return_value_policy::move)
        .def("GetSystemMetricsHistory", [](py::object self, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXSystemMetricsListPtr systemMetricsList;
        perfMetrics->GetSystemMetricsHistory(startMs, stopMs, &systemMetricsList);
        std::vector<IADLXSystemMetricsPtr> list;
        if (systemMetricsList)
        {
            for (adlx_uint s = systemMetricsList->Begin(); s != systemMetricsList->End(); s++) {
                IADLXSystemMetricsPtr item;
                systemMetricsList->At(s, &item);
                list.emplace_back(std::move(item));
            }
        }
        return list;
        }, py::return_value_policy::move)
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXPerformanceMonitoringServicesPtr ppInterface = nullptr;
        perfMetrics->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move)
        
        // Custom Methods
        .def("GetAllMetricsHistoryRaw", [](py::object self, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXAllMetricsListPtr allMetricsList;
        perfMetrics->GetAllMetricsHistory(startMs, stopMs, &allMetricsList);
        return allMetricsList;
        }, py::return_value_policy::move)
        .def("GetFPSHistoryRaw", [](py::object self, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXFPSListPtr fpsList;
        perfMetrics->GetFPSHistory(startMs, stopMs, &fpsList);
        return fpsList;
        }, py::return_value_policy::move)
        .def("GetGPUMetricsHistoryRaw", [](py::object self, IADLXGPUPtr oneGPU, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXGPUMetricsListPtr gpuMetricsList;
        perfMetrics->GetGPUMetricsHistory(oneGPU, startMs, stopMs, &gpuMetricsList);
        return gpuMetricsList;
        }, py::return_value_policy::move)
        .def("GetSystemMetricsHistoryRaw", [](py::object self, adlx_int startMs, adlx_int stopMs) {
        IADLXPerformanceMonitoringServicesPtr perfMetrics = self.cast<IADLXPerformanceMonitoringServices*>();
        IADLXSystemMetricsListPtr systemMetricsList;
        perfMetrics->GetSystemMetricsHistory(startMs, stopMs, &systemMetricsList);
        return systemMetricsList;
        }, py::return_value_policy::move);


    // SystemMetricsSupport
    py::class_<IADLXSystemMetricsSupport, IADLXInterface, PySystemMetricsSupport, IADLXInterfacePtr_T<IADLXSystemMetricsSupport>>(m, "IADLXSystemMetricsSupport")
        //.def(py::init<>())
        .def("IsSupportedCPUUsage", [](py::object self) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedCPUUsage(&supported);
        return supported;
        })
        .def("IsSupportedSystemRAM", [](py::object self) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedSystemRAM(&supported);
        return supported;
        })
        .def("IsSupportedSmartShift", [](py::object self) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedSmartShift(&supported);
        return supported;
        })
        .def("GetCPUUsageRange", [](py::object self) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetCPUUsageRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetSystemRAMRange", [](py::object self) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetSystemRAMRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetSmartShiftRange", [](py::object self) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetSmartShiftRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("IsSupportedPowerDistribution", [](py::object self) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        adlx_bool supported = false;
        IADLXSystemMetricsSupport1Ptr perfMetrics1(perfMetrics);
        if (perfMetrics1)
        {
            perfMetrics1->IsSupportedPowerDistribution(&supported);
        }
        return supported;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXSystemMetricsSupportPtr perfMetrics = self.cast<IADLXSystemMetricsSupport*>();
        IADLXSystemMetricsSupportPtr ppInterface = nullptr;
        perfMetrics->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    //IADLXSystemMetrics 
    py::class_<IADLXSystemMetrics, IADLXInterface, PySystemMetrics, IADLXInterfacePtr_T<IADLXSystemMetrics>>(m, "IADLXSystemMetrics")
        //.def(py::init<>())
        .def("TimeStamp", [](py::object self) -> std::variant<adlx_int64, py::none> {
        IADLXSystemMetricsPtr sysMetrics = self.cast<IADLXSystemMetrics*>();
        adlx_int64 ms;
        ADLX_RESULT ret = sysMetrics->TimeStamp(&ms);
        if (ADLX_SUCCEEDED(ret))
            return ms;
        return py::none();
        })
        .def("CPUUsage", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXSystemMetricsPtr sysMetrics = self.cast<IADLXSystemMetrics*>();
        adlx_double cpuUsage;
        ADLX_RESULT ret = sysMetrics->CPUUsage(&cpuUsage);
        if (ADLX_SUCCEEDED(ret))
            return cpuUsage;
        return py::none();
        })
        .def("SystemRAM", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXSystemMetricsPtr sysMetrics = self.cast<IADLXSystemMetrics*>();
        adlx_int systemRAM;
        ADLX_RESULT ret = sysMetrics->SystemRAM(&systemRAM);
        if (ADLX_SUCCEEDED(ret))
            return systemRAM;
        return py::none();
        })
        .def("SmartShift", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXSystemMetricsPtr sysMetrics = self.cast<IADLXSystemMetrics*>();
        adlx_int smartshift;
        ADLX_RESULT ret = sysMetrics->SmartShift(&smartshift);
        if (ADLX_SUCCEEDED(ret))
            return smartshift;
        return py::none();
        })
        .def("PowerDistribution", [](py::object self) {
        IADLXSystemMetricsPtr sysMetrics = self.cast<IADLXSystemMetrics*>();
        adlx_int apuShiftValue = 0; adlx_int gpuShiftValue = 0; adlx_int apuShiftLimit = 0; adlx_int gpuShiftLimit = 0; adlx_int totalShiftLimit = 0;
        IADLXSystemMetrics1Ptr sysMetrics1(sysMetrics);
        if (sysMetrics1)
        {
            sysMetrics1->PowerDistribution(&apuShiftValue, &gpuShiftValue, &apuShiftLimit, &gpuShiftLimit, &totalShiftLimit);
        }
        return std::tuple<adlx_int, adlx_int, adlx_int, adlx_int, adlx_int>(apuShiftValue, gpuShiftValue, apuShiftLimit, gpuShiftLimit, totalShiftLimit);
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXSystemMetricsPtr sysMetrics = self.cast<IADLXSystemMetrics*>();
        IADLXSystemMetricsPtr ppInterface = nullptr;
        sysMetrics->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // IADLXGPUMetricsSupport
    py::class_<IADLXGPUMetricsSupport, IADLXInterface, PyGPUMetricsSupport, IADLXInterfacePtr_T<IADLXGPUMetricsSupport>>(m, "IADLXGPUMetricsSupport")
        //.def(py::init<>())
        .def("IsSupportedGPUUsage", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUUsage(&supported);
        return supported;
        })
        .def("IsSupportedGPUClockSpeed", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUClockSpeed(&supported);
        return supported;
        })
        .def("IsSupportedGPUVRAMClockSpeed", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUVRAMClockSpeed(&supported);
        return supported;
        })
        .def("IsSupportedGPUTemperature", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUTemperature(&supported);
        return supported;
        })
        .def("IsSupportedGPUHotspotTemperature", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUHotspotTemperature(&supported);
        return supported;
        })
        .def("IsSupportedGPUPower", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUPower(&supported);
        return supported;
        })
        .def("IsSupportedGPUTotalBoardPower", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUTotalBoardPower(&supported);
        return supported;
        })
        .def("IsSupportedGPUFanSpeed", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUFanSpeed(&supported);
        return supported;
        })
        .def("IsSupportedGPUVRAM", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUVRAM(&supported);
        return supported;
        })
        .def("IsSupportedGPUVoltage", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUVoltage(&supported);
        return supported;
        })
        .def("IsSupportedGPUIntakeTemperature", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        perfMetrics->IsSupportedGPUIntakeTemperature(&supported);
        return supported;
        })
        .def("GetGPUUsageRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUUsageRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUClockSpeedRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUClockSpeedRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUVRAMClockSpeedRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUVRAMClockSpeedRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUTemperatureRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUTemperatureRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUHotspotTemperatureRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUHotspotTemperatureRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUPowerRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUPowerRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUFanSpeedRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUFanSpeedRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUVRAMRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUVRAMRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUVoltageRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUVoltageRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUTotalBoardPowerRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;	
        perfMetrics->GetGPUTotalBoardPowerRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("GetGPUIntakeTemperatureRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue;
        adlx_int maxValue;
        perfMetrics->GetGPUIntakeTemperatureRange(&minValue, &maxValue);
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("IsSupportedGPUMemoryTemperature", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        IADLXGPUMetricsSupport1Ptr perfMetrics1(perfMetrics);
        if (perfMetrics1)
        {
            perfMetrics1->IsSupportedGPUMemoryTemperature(&supported);
        }
        return supported;
        })
        .def("GetGPUMemoryTemperatureRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue = 0;
        adlx_int maxValue = 0;
        IADLXGPUMetricsSupport1Ptr perfMetrics1(perfMetrics);
        if (perfMetrics1)
        {
            perfMetrics1->GetGPUMemoryTemperatureRange(&minValue, &maxValue);
        }
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("IsSupportedNPUFrequency", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        IADLXGPUMetricsSupport1Ptr perfMetrics1(perfMetrics);
        if (perfMetrics1)
        {
            perfMetrics1->IsSupportedNPUFrequency(&supported);
        }
        return supported;
        })
        .def("GetNPUFrequencyRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue = 0;
        adlx_int maxValue = 0;
        IADLXGPUMetricsSupport1Ptr perfMetrics1(perfMetrics);
        if (perfMetrics1)
        {
            perfMetrics1->GetNPUFrequencyRange(&minValue, &maxValue);
        }
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("IsSupportedNPUActivityLevel", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        IADLXGPUMetricsSupport1Ptr perfMetrics1(perfMetrics);
        if (perfMetrics1)
        {
            perfMetrics1->IsSupportedNPUActivityLevel(&supported);
        }
        return supported;
        })
        .def("GetNPUActivityLevelRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue = 0;
        adlx_int maxValue = 0;
        IADLXGPUMetricsSupport1Ptr perfMetrics1(perfMetrics);
        if (perfMetrics1)
        {
            perfMetrics1->GetNPUActivityLevelRange(&minValue, &maxValue);
        }
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("IsSupportedGPUSharedMemory", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        IADLXGPUMetricsSupport2Ptr perfMetrics2(perfMetrics);
        if (perfMetrics2)
        {
            perfMetrics2->IsSupportedGPUSharedMemory(&supported);
        }
        return supported;
        })
        .def("GetGPUSharedMemoryRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue = 0;
        adlx_int maxValue = 0;
        IADLXGPUMetricsSupport2Ptr perfMetrics2(perfMetrics);
        if (perfMetrics2)
        {
            perfMetrics2->GetGPUSharedMemoryRange(&minValue, &maxValue);
        }
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("IsSupportedGPUFanDuty", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_bool supported = false;
        IADLXGPUMetricsSupport3Ptr perfMetrics3(perfMetrics);
        if (perfMetrics3)
        {
            perfMetrics3->IsSupportedGPUFanDuty(&supported);
        }
        return supported;
        })
        .def("GetGPUFanDutyRange", [](py::object self) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        adlx_int minValue = 0;
        adlx_int maxValue = 0;
        IADLXGPUMetricsSupport3Ptr perfMetrics3(perfMetrics);
        if (perfMetrics3)
        {
            perfMetrics3->GetGPUFanDutyRange(&minValue, &maxValue);
        }
        return std::tuple<adlx_int, adlx_int>(minValue, maxValue);
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUMetricsSupportPtr perfMetrics = self.cast<IADLXGPUMetricsSupport*>();
        IADLXGPUMetricsSupportPtr ppInterface = nullptr;
        perfMetrics->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    //GPU metrics
    py::class_<IADLXGPUMetrics, IADLXInterface, PyGPUMetrics, IADLXInterfacePtr_T<IADLXGPUMetrics>>(m, "IADLXGPUMetrics")
        //.def(py::init<>())
        .def("GPUClockSpeed", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data;
        ADLX_RESULT ret = gpuMetrics->GPUClockSpeed(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUFanSpeed", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data;
        ADLX_RESULT ret = gpuMetrics->GPUFanSpeed(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUHotspotTemperature", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_double data;
        ADLX_RESULT ret = gpuMetrics->GPUHotspotTemperature(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUPower", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_double data;
        ADLX_RESULT ret = gpuMetrics->GPUPower(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUTemperature", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_double data;
        ADLX_RESULT ret = gpuMetrics->GPUTemperature(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUTotalBoardPower", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_double data;
        ADLX_RESULT ret = gpuMetrics->GPUTotalBoardPower(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUUsage", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_double data;
        ADLX_RESULT ret = gpuMetrics->GPUUsage(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUVRAM", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data;
        ADLX_RESULT ret = gpuMetrics->GPUVRAM(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUVRAMClockSpeed", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data;
        ADLX_RESULT ret = gpuMetrics->GPUVRAMClockSpeed(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUVoltage", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data;
        ADLX_RESULT ret = gpuMetrics->GPUVoltage(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("TimeStamp", [](py::object self) -> std::variant<adlx_int64, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int64 ms;
        ADLX_RESULT ret = gpuMetrics->TimeStamp(&ms);
        if (ADLX_SUCCEEDED(ret))
            return ms;
        return py::none();
        })
        .def("GPUIntakeTemperature", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_double data = 0;
        ADLX_RESULT ret = gpuMetrics->GPUIntakeTemperature(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("GPUMemoryTemperature", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_double data = 0;
        IADLXGPUMetrics1Ptr gpuMetrics1(gpuMetrics);
        if (gpuMetrics1)
        {
            ADLX_RESULT ret = gpuMetrics1->GPUMemoryTemperature(&data);
            if (ADLX_SUCCEEDED(ret))
                return data;
        }
        return py::none();
        })
        .def("NPUFrequency", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data = 0;
        IADLXGPUMetrics1Ptr gpuMetrics1(gpuMetrics);
        if (gpuMetrics1)
        {
            ADLX_RESULT ret = gpuMetrics1->NPUFrequency(&data);
            if (ADLX_SUCCEEDED(ret))
                return data;
        }
        return py::none();
        })
        .def("NPUActivityLevel", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data = 0;
        IADLXGPUMetrics1Ptr gpuMetrics1(gpuMetrics);
        if (gpuMetrics1)
        {
            ADLX_RESULT ret = gpuMetrics1->NPUActivityLevel(&data);
            if (ADLX_SUCCEEDED(ret))
                return data;
        }
        return py::none();
        })
        .def("GPUSharedMemory", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data = 0;
        IADLXGPUMetrics2Ptr gpuMetrics2(gpuMetrics);
        if (gpuMetrics2)
        {
            ADLX_RESULT ret = gpuMetrics2->GPUSharedMemory(&data);
            if (ADLX_SUCCEEDED(ret))
                return data;
        }
        return py::none();
        })
        .def("GPUFanDuty", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        adlx_int data = 0;
        IADLXGPUMetrics3Ptr gpuMetrics3(gpuMetrics);
        if (gpuMetrics3)
        {
            ADLX_RESULT ret = gpuMetrics3->GPUFanDuty(&data);
            if (ADLX_SUCCEEDED(ret))
                return data;
        }
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUMetricsPtr gpuMetrics = self.cast<IADLXGPUMetrics*>();
        IADLXGPUMetricsPtr ppInterface = nullptr;
        gpuMetrics->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    //IADLXFPS 
    py::class_<IADLXFPS, IADLXInterface, PyFPS, IADLXInterfacePtr_T<IADLXFPS>>(m, "IADLXFPS")
        //.def(py::init<>())
        .def("TimeStamp", [](py::object self) -> std::variant<adlx_int64, py::none> {
        IADLXFPSPtr sysMetrics = self.cast<IADLXFPS*>();
        adlx_int64 ms;
        ADLX_RESULT ret = sysMetrics->TimeStamp(&ms);
        if (ADLX_SUCCEEDED(ret))
            return ms;
        return py::none();
        })
        .def("FPS", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXFPSPtr sysMetrics = self.cast<IADLXFPS*>();
        adlx_int data = -1;
        ADLX_RESULT ret = sysMetrics->FPS(&data);
        if (ADLX_SUCCEEDED(ret))
            return data;
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXFPSPtr sysMetrics = self.cast<IADLXFPS*>();
        IADLXFPSPtr ppInterface = nullptr;
        sysMetrics->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    //IADLXAllMetrics 
    py::class_<IADLXAllMetrics, IADLXInterface, PyAllMetrics, IADLXInterfacePtr_T<IADLXAllMetrics>>(m, "IADLXAllMetrics")
        //.def(py::init<>())
        .def("TimeStamp", [](py::object self) -> std::variant<adlx_int64, py::none> {
        IADLXAllMetricsPtr sysMetrics = self.cast<IADLXAllMetrics*>();
        adlx_int64 ms;
        ADLX_RESULT ret = sysMetrics->TimeStamp(&ms);
        if (ADLX_SUCCEEDED(ret))
            return ms;
        return py::none();
        })
        .def("GetSystemMetrics", [](py::object self) {
        IADLXAllMetricsPtr sysMetrics = self.cast<IADLXAllMetrics*>();
        IADLXSystemMetricsPtr ppSystemMetrics;
        sysMetrics->GetSystemMetrics(&ppSystemMetrics);
        return ppSystemMetrics;
        })
        .def("GetFPS", [](py::object self) {
        IADLXAllMetricsPtr sysMetrics = self.cast<IADLXAllMetrics*>();
        IADLXFPSPtr ppFPS;
        sysMetrics->GetFPS(&ppFPS);
        return ppFPS;
        })
        .def("GetGPUMetrics", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXAllMetricsPtr sysMetrics = self.cast<IADLXAllMetrics*>();
        IADLXGPUMetricsPtr ppGPUMetrics;
        sysMetrics->GetGPUMetrics(oneGPU, &ppGPUMetrics);
        return ppGPUMetrics;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXAllMetricsPtr sysMetrics = self.cast<IADLXAllMetrics*>();
        IADLXAllMetricsPtr ppInterface = nullptr;
        sysMetrics->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // AllMetricsList
        py::class_<IADLXAllMetricsList, IADLXList, PyAllMetricsList, IADLXInterfacePtr_T<IADLXAllMetricsList>>(m, "IADLXAllMetricsList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXAllMetrics* pItem) {
        IADLXAllMetricsListPtr allMetricsList = self.cast<IADLXAllMetricsList*>();
        ADLX_RESULT retAllMetricsList = allMetricsList->Add_Back(pItem);
        return retAllMetricsList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXAllMetricsListPtr allMetricsList = self.cast<IADLXAllMetricsList*>();
        IADLXAllMetricsPtr ppItem;
        allMetricsList->At(location, &ppItem);
        return ppItem;
        });

        // FPSList
        py::class_<IADLXFPSList, IADLXList, PyFPSList, IADLXInterfacePtr_T<IADLXFPSList>>(m, "IADLXFPSList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXFPS* pItem) {
        IADLXFPSListPtr fpsList = self.cast<IADLXFPSList*>();
        ADLX_RESULT retFPSList = fpsList->Add_Back(pItem);
        return retFPSList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXFPSListPtr fpsList = self.cast<IADLXFPSList*>();
        IADLXFPSPtr ppItem;
        fpsList->At(location, &ppItem);
        return ppItem;
        });


        // GPUMetricsList
        py::class_<IADLXGPUMetricsList, IADLXList, PyGPUMetricsList, IADLXInterfacePtr_T<IADLXGPUMetricsList>>(m, "IADLXGPUMetricsList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXGPUMetrics* pItem) {
        IADLXGPUMetricsListPtr gpuMetricsList = self.cast<IADLXGPUMetricsList*>();
        ADLX_RESULT retGPUMetricsList = gpuMetricsList->Add_Back(pItem);
        return retGPUMetricsList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXGPUMetricsListPtr gpuMetricsList = self.cast<IADLXGPUMetricsList*>();
        IADLXGPUMetricsPtr ppItem;
        gpuMetricsList->At(location, &ppItem);
        return ppItem;
        });


        // SystemMetricsList
        py::class_<IADLXSystemMetricsList, IADLXList, PySystemMetricsList, IADLXInterfacePtr_T<IADLXSystemMetricsList>>(m, "IADLXSystemMetricsList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXSystemMetrics* pItem) {
        IADLXSystemMetricsListPtr systemMetricsList = self.cast<IADLXSystemMetricsList*>();
        ADLX_RESULT retSystemMetricsList = systemMetricsList->Add_Back(pItem);
        return retSystemMetricsList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXSystemMetricsListPtr systemMetricsList = self.cast<IADLXSystemMetricsList*>();
        IADLXSystemMetricsPtr ppItem;
        systemMetricsList->At(location, &ppItem);
        return ppItem;
        });

}
