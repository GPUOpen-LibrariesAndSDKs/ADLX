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
            self._display_service: Optional[ADLX.IADLXDisplayServices] = None
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
    def display_service(self) -> ADLX.IADLXDisplayServices:
        """Cached display services."""
        if self._display_service is None:
            self._display_service = self.system.GetDisplaysServices()
        return self._display_service
    
    @property
    def display_list(self) -> List[ADLX.IADLXDisplay]:
        """Cached list of displays."""
        return self.display_service.GetDisplays()
    
    def get_display_custom_color(self, display: ADLX.IADLXDisplay) -> ADLX.IADLXDisplayCustomColor:
        """Cached display custom color service."""
        return self.display_service.GetCustomColor(display)
    
    def get_display_custom_resolution(self, display: ADLX.IADLXDisplay) -> ADLX.IADLXDisplayCustomResolution :
        """Cached display custom resolution service."""
        return self.display_service.GetCustomResolution(display)
    
    def get_display_vsr(self, display: ADLX.IADLXDisplay) -> ADLX.IADLXDisplayVSR:
        """Cached display VSR service."""
        return self.display_service.GetVirtualSuperResolution(display)
