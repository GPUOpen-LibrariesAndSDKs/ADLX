//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

use super::*;

// -------------------------------------------------------------------------------------------------
// Desktops (see SDK/Include/IDesktops.h)
// -------------------------------------------------------------------------------------------------
/// `ADLX_Point` (see SDK/Include/ADLXStructures.h).
#[repr(C)]
pub struct ADLX_Point {
    pub x: adlx_int,
    pub y: adlx_int,
}

#[repr(C)]
pub struct IADLXDesktopServicesVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDesktopServices) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDesktopServices) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopServices,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub GetNumberOfDesktops: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopServices,
        pNumDesktops: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetDesktops: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopServices,
        ppDesktops: *mut *mut IADLXDesktopList,
    ) -> ADLX_RESULT,
    pub GetDesktopChangedHandling: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopServices,
        ppDesktopChangedHandling: *mut *mut IADLXDesktopChangedHandling,
    ) -> ADLX_RESULT,
    pub GetSimpleEyefinity: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopServices,
        ppSimpleEyefinity: *mut *mut IADLXSimpleEyefinity,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDesktopServices {
    pub pVtbl: *const IADLXDesktopServicesVtbl,
}

#[repr(C)]
pub struct IADLXDesktopListVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopList,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Size: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> adlx_uint,
    pub Empty: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> adlx_bool,
    pub Begin: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> adlx_uint,
    pub End: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> adlx_uint,
    pub At: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopList,
        location: adlx_uint,
        ppItem: *mut *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub Clear: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> ADLX_RESULT,
    pub Remove_Back: unsafe extern "system" fn(pThis: *mut IADLXDesktopList) -> ADLX_RESULT,
    pub Add_Back: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopList,
        pItem: *mut IADLXInterface,
    ) -> ADLX_RESULT,
    pub At_DesktopList: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopList,
        location: adlx_uint,
        ppItem: *mut *mut IADLXDesktop,
    ) -> ADLX_RESULT,
    pub Add_Back_DesktopList: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopList,
        pItem: *mut IADLXDesktop,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDesktopList {
    pub pVtbl: *const IADLXDesktopListVtbl,
}

#[repr(C)]
pub struct IADLXDesktopVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDesktop) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDesktop) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDesktop,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub Orientation:
        unsafe extern "system" fn(pThis: *mut IADLXDesktop, orientation: *mut c_int) -> ADLX_RESULT,
    pub Size: unsafe extern "system" fn(
        pThis: *mut IADLXDesktop,
        width: *mut adlx_int,
        height: *mut adlx_int,
    ) -> ADLX_RESULT,
    pub TopLeft: unsafe extern "system" fn(
        pThis: *mut IADLXDesktop,
        locationTopLeft: *mut ADLX_Point,
    ) -> ADLX_RESULT,
    pub Type:
        unsafe extern "system" fn(pThis: *mut IADLXDesktop, desktopType: *mut c_int) -> ADLX_RESULT,
    pub GetNumberOfDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDesktop,
        numDisplays: *mut adlx_uint,
    ) -> ADLX_RESULT,
    pub GetDisplays: unsafe extern "system" fn(
        pThis: *mut IADLXDesktop,
        ppDisplays: *mut *mut IADLXDisplayList,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDesktop {
    pub pVtbl: *const IADLXDesktopVtbl,
}

/// Vtable for an application-implemented `IADLXDesktopListChangedListener`.
#[repr(C)]
pub struct IADLXDesktopListChangedListenerVtbl {
    pub OnDesktopListChanged: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopListChangedListener,
        pNewDesktop: *mut IADLXDesktopList,
    ) -> adlx_bool,
}

#[repr(C)]
pub struct IADLXDesktopListChangedListener {
    pub pVtbl: *const IADLXDesktopListChangedListenerVtbl,
}

#[repr(C)]
pub struct IADLXDesktopChangedHandlingVtbl {
    pub Acquire: unsafe extern "system" fn(pThis: *mut IADLXDesktopChangedHandling) -> adlx_long,
    pub Release: unsafe extern "system" fn(pThis: *mut IADLXDesktopChangedHandling) -> adlx_long,
    pub QueryInterface: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopChangedHandling,
        interfaceId: *const u16,
        ppInterface: *mut *mut c_void,
    ) -> ADLX_RESULT,
    pub AddDesktopListEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopChangedHandling,
        pListener: *mut IADLXDesktopListChangedListener,
    ) -> ADLX_RESULT,
    pub RemoveDesktopListEventListener: unsafe extern "system" fn(
        pThis: *mut IADLXDesktopChangedHandling,
        pListener: *mut IADLXDesktopListChangedListener,
    ) -> ADLX_RESULT,
}

#[repr(C)]
pub struct IADLXDesktopChangedHandling {
    pub pVtbl: *const IADLXDesktopChangedHandlingVtbl,
}
