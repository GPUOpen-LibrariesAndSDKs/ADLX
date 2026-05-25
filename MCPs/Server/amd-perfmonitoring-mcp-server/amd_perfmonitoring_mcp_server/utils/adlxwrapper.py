from adlx import ADLX
from typing import List, Optional,Dict

class ADLXAPIWrapper:
    """Wrapper for ADLX API with optimized caching and resource management."""

    _instance = None
    adlx_helper = ADLX.ADLXHelper()
    
    def __new__(cls):
        """Implement singleton pattern to avoid multiple initializations."""
        if cls._instance is None:
            cls._instance = super(ADLXAPIWrapper, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance

    def __init__(self):
        """Initialize ADLX with caching."""
        if not self._initialized:
            self.adlx_helper.Initialize()
            self._system: Optional[ADLX.IADLXSystem] = None
            self._performance_monitoring_service: Optional[ADLX.IADLXPerformanceMonitoringServices] = None
            self._initialized = True
    
    def __del__(self):
        """Clean up ADLX resources."""
        if hasattr(self, '_initialized') and self._initialized:
            self.adlx_helper.Terminate()
            self._initialized = False
    
    @property
    def system(self) -> ADLX.IADLXSystem:
        """Cached system services."""
        if self._system is None:
            self._system = self.adlx_helper.GetSystemServices()
        return self._system
    
    @property
    def gpus(self) -> List[ADLX.IADLXGPU]:
        """Cached list of GPUs."""
        self._gpus = []
        for gpu in self.system.GetGPUs():
            if gpu.Type() != ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
                self._gpus.append(gpu)
        return self._gpus
    
    @property
    def performance_monitoring_service(self) -> ADLX.IADLXPerformanceMonitoringServices:
        """Cached performance monitoring services."""
        if self._performance_monitoring_service is None:
            self._performance_monitoring_service = self.system.GetPerformanceMonitoringServices()
        return self._performance_monitoring_service

    def get_gpu_metrics(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXGPUMetrics:
        """Get current GPU metrics for a specific GPU."""
        metrics = self.performance_monitoring_service.GetCurrentGPUMetrics(gpu)
        assert isinstance(metrics, ADLX.IADLXGPUMetrics)
        return metrics

    def get_gpu_metrics_support(self, gpu: ADLX.IADLXGPU) -> ADLX.IADLXGPUMetricsSupport:
        """Get supported GPU metrics."""
        support = self.performance_monitoring_service.GetSupportedGPUMetrics(gpu)
        assert isinstance(support, ADLX.IADLXGPUMetricsSupport)
        return support

    def get_system_metrics(self) -> ADLX.IADLXSystemMetrics:
        """Get current system metrics."""
        metrics = self.performance_monitoring_service.GetCurrentSystemMetrics()
        assert isinstance(metrics, ADLX.IADLXSystemMetrics)
        return metrics

    def get_system_metrics_support(self) -> ADLX.IADLXSystemMetricsSupport:
        """Get supported system metrics."""
        support = self.performance_monitoring_service.GetSupportedSystemMetrics()
        assert isinstance(support, ADLX.IADLXSystemMetricsSupport)
        return support
    
    def get_current_fps(self) -> ADLX.IADLXFPS:
        """Get current FPS."""
        fps = self.performance_monitoring_service.GetCurrentFPS()
        assert isinstance(fps, ADLX.IADLXFPS)
        return fps
