#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for Display service interfaces methods  """
import pytest

from typing import List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


# Callback
def callback_display_gamma_changed(p_display_gamma_changed_listener) -> bool:
    display: ADLX.IADLXDisplay = p_display_gamma_changed_listener.GetDisplay()
    assert isinstance(display, ADLX.IADLXDisplay)

    is_de_gamma_changed = p_display_gamma_changed_listener.IsReGammaChanged()
    assert isinstance(is_de_gamma_changed, bool)
    is_gamma_coefficient_changed = p_display_gamma_changed_listener.IsGammaCoefficientChanged()
    assert isinstance(is_gamma_coefficient_changed, bool)
    is_gamma_ramp_changed = p_display_gamma_changed_listener.IsGammaRampChanged()
    assert isinstance(is_gamma_ramp_changed, bool)
    is_re_gamma_changed = p_display_gamma_changed_listener.IsReGammaChanged()
    assert isinstance(is_re_gamma_changed, bool)

    return True


def test_get_gamma_coefficient(adlx):
    """call GetGammaCoefficient() on IADLXDisplayGamma interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        coeff: ADLX.ADLX_RegammaCoeff = gama.GetGammaCoefficient()
        assert isinstance(coeff, ADLX.ADLX_RegammaCoeff)
        assert isinstance(coeff.coefficientA0, int)
        assert isinstance(coeff.coefficientA1, int)
        assert isinstance(coeff.coefficientA2, int)
        assert isinstance(coeff.coefficientA3, int)
        assert isinstance(coeff.gamma, int)
        del coeff, gama
    del display_list, display_service, system


def test_get_gamma_ramp(adlx):
    """call GetGammaRamp() on IADLXDisplayGamma interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        gamma_ramp: List[str] = gamma.GetGammaRamp()
        assert isinstance(gamma_ramp, list)
        assert len(gamma_ramp) == 768
        del gamma_ramp, gamma
    del display_list, display_service, system


# def test_set_de_gamma_ramp_memory(adlx):
#     """call SetDeGammaRampMemory() with memory buffer data on IADLXDisplayGamma interface."""
#     system: ADLX.IADLXSystem = adlx.GetSystemServices()
#     display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
#     display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
#     for display in display_list:
#         gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
#         gamma_ramp_data: List[str] = [255] * 256 * 3

#         ret_set: ADLX.ADLX_RESULT = gamma.SetDeGammaRampMemory(gamma_ramp_data)
#         assert ret_set == ADLX.ADLX_RESULT.ADLX_OK


def test_set_de_gamma_ramp_file(adlx):
    """call SetDeGammaRampFile() with memory buffer data on IADLXDisplayGamma interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        gamma_ramp_from_file: str = "gamma_ramp_input_for_tests.txt"

        ret_set: ADLX.ADLX_RESULT = gamma.SetDeGammaRampFile(gamma_ramp_from_file)
        assert isinstance(ret_set, ADLX.ADLX_RESULT)
        del gamma
    del display_list, display_service, system

def create_re_gamma_ramp(f_gamma: float) -> list:
    """Create regamma ramp."""
    ramp = [0] * 768
    g_f_gamma_remap_rgb = [1.0, 1.0, 0.5]
    for j in range(3):
        for i in range(256):
            n_adj = i / 255.0
            if n_adj < 0.0031308:
                n_adj = n_adj * 12.92
            else:
                n_adj = (1 + 0.055) * pow(n_adj, 1.0 / f_gamma) - 0.055
                if n_adj < 0.0:
                    n_adj = 0.0
            ramp[i + j * 256] = int(1 * g_f_gamma_remap_rgb[j] * int(n_adj * 0xFFFF))
    return ramp

def test_set_re_gamma_ramp_memory(adlx):
    """call SetReGammaRampMemory() with memory buffer data on IADLXDisplayGamma interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        gamma_ramp_data: List[float] = create_re_gamma_ramp(2.4)

        ret_set: ADLX.ADLX_RESULT = gamma.SetReGammaRampMemory(gamma_ramp_data)
        assert isinstance(ret_set, ADLX.ADLX_RESULT)
        del gamma
    del display_list, display_service, system


def test_set_re_gamma_ramp_file(adlx):
    """call SetReGammaRampFile() with memory buffer data on IADLXDisplayGamma interface."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    for display in display_list:
        gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        gamma_ramp_from_file: str = "gamma_ramp_input_for_tests.txt"

        ret_set: ADLX.ADLX_RESULT = gamma.SetReGammaRampFile(gamma_ramp_from_file)
        assert isinstance(ret_set, ADLX.ADLX_RESULT)
        del gamma
    del display_list, display_service, system


def _get_display_gamma_list(adlx):
    """Helper: return (display_service, display_list) or skip if no displays."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()
    display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
    if not display_list:
        del display_service, system
        pytest.skip("No Displays found")
    return system, display_service, display_list


def test_is_current_DeGamma_ramp(adlx):
    """call IsCurrentDeGammaRamp() on IADLXDisplayGamma interface."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentDeGammaRamp(), bool)
        del get_gama
    del display_list, display_service, system


def test_is_current_DeGamma_36(adlx):
    """call IsCurrentReGamma36() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentReGamma36(), bool)
        del get_gama
    del display_list, display_service, system


def test_is_current_regamma_BT709(adlx):
    """call IsCurrentReGammaBT709() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentReGammaBT709(), bool)
        del get_gama
    del display_list, display_service, system


def test_is_current_regamma_PQ(adlx):
    """call IsCurrentReGammaPQ() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentReGammaPQ(), bool)
        del get_gama
    del display_list, display_service, system


def test_is_current_regamma_PQ2084_interim(adlx):
    """call IsCurrentReGammaPQ2084Interim() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentReGammaPQ2084Interim(), bool)
        del get_gama
    del display_list, display_service, system


def test_is_current_regamma_ramp(adlx):
    """call IsCurrentReGammaRamp() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentReGammaRamp(), bool)
        del get_gama
    del display_list, display_service, system


def test_is_current_regamma_SRGB(adlx):
    """call IsCurrentReGammaSRGB() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentReGammaSRGB(), bool)
        del get_gama
    del display_list, display_service, system


def test_is_current_regamma_coefficient(adlx):
    """call IsCurrentRegammaCoefficient() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsCurrentRegammaCoefficient(), bool)
        del get_gama
    del display_list, display_service, system


def test_supported_regamma_36(adlx):
    """call IsSupportedReGamma36() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsSupportedReGamma36(), bool)
        del get_gama
    del display_list, display_service, system


def test_supported_regamma_BT709(adlx):
    """call IsSupportedReGammaBT709() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsSupportedReGammaBT709(), bool)
        del get_gama
    del display_list, display_service, system


def test_supported_regamma_PQ(adlx):
    """call IsSupportedReGammaPQ() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsSupportedReGammaPQ(), bool)
        del get_gama
    del display_list, display_service, system


def test_supported_regamma_PQ2084_interim(adlx):
    """call IsSupportedReGammaPQ2084Interim() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsSupportedReGammaPQ2084Interim(), bool)
        del get_gama
    del display_list, display_service, system


def test_supported_regamma_SRGB(adlx):
    """call IsSupportedReGammaSRGB() on IADLXDisplayGamma interface.Expect bool response."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.IsSupportedReGammaSRGB(), bool)
        del get_gama
    del display_list, display_service, system


def test_reset_gamma_ramp(adlx):
    """call ResetGammaRamp() on IADLXDisplayGamma interface.We expect non-empty response. No errors"""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.ResetGammaRamp(), ADLX.ADLX_RESULT)
        del get_gama
    del display_list, display_service, system


def test_set_regamma_36(adlx):
    """call SetReGamma36() on IADLXDisplayGamma interface.We expect non-empty response. No errors"""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.SetReGamma36(), ADLX.ADLX_RESULT)
        del get_gama
    del display_list, display_service, system


def test_set_regamma_BT709(adlx):
    """call SetReGammaBT709() on IADLXDisplayGamma interface.We expect non-empty response. No errors"""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.SetReGammaBT709(), ADLX.ADLX_RESULT)
        del get_gama
    del display_list, display_service, system


def test_set_regamma_PQ(adlx):
    """call SetReGammaPQ() on IADLXDisplayGamma interface.We expect non-empty response. No errors"""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.SetReGammaPQ(), ADLX.ADLX_RESULT)
        del get_gama
    del display_list, display_service, system


def test_set_regamma_PQ2084_interim(adlx):
    """call SetReGammaPQ2084Interim() on IADLXDisplayGamma interface.We expect non-empty response. No errors"""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.SetReGammaPQ2084Interim(), ADLX.ADLX_RESULT)
        del get_gama
    del display_list, display_service, system


def test_set_regamma_SRGB(adlx):
    """call SetReGammaSRGB() on IADLXDisplayGamma interface.We expect non-empty response. No errors"""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        get_gama: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        assert isinstance(get_gama.SetReGammaSRGB(), ADLX.ADLX_RESULT)
        del get_gama
    del display_list, display_service, system


def test_set_re_gamma_coefficient_gamma(adlx):
    """call SetReGammaCoefficient() on IADLXDisplayGamma interface."""
    system, display_service, display_list = _get_display_gamma_list(adlx)
    for display in display_list:
        gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
        coeff: ADLX.ADLX_RegammaCoeff = ADLX.ADLX_RegammaCoeff()

        coeff.coefficientA0 = 31308
        coeff.coefficientA1 = 12920
        coeff.coefficientA2 = 55
        coeff.coefficientA3 = 55
        coeff.gamma = 2400

        ret_api: ADLX.ADLX_RESULT = gamma.SetReGammaCoefficient(coeff)
        assert isinstance(ret_api, ADLX.ADLX_RESULT)
        del coeff, gamma
    del display_list, display_service, system


# def test_add_display_gamma_event_listener_gamma(adlx):
#     """Test Gamma events AddDisplayGammaEventListener()"""
#     system: ADLX.IADLXSystem = adlx.GetSystemServices()
#     display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

#     display_change_handler: ADLX.IADLXDisplayServices = display_service.GetDisplayChangedHandling()

#     callback: ADLX.PyDisplayGammaChangedListenerCallback = ADLX.PyDisplayGammaChangedListenerCallback()
#     callback.call = callback_display_gamma_changed

#     res_add_gamut_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplayGammaEventListener(callback)
#     assert res_add_gamut_listener == ADLX.ADLX_RESULT.ADLX_OK

#     # test callback methods, trigger some gamma change
#     display_list: List[ADLX.IADLXDisplay] = display_service.GetDisplays()
#     for display in display_list:
#         gamma: ADLX.IADLXDisplayGamma = display_service.GetGamma(display)
#         gamma_ramp_data: List[str] = [255] * 256 * 3

#         ret_set: ADLX.ADLX_RESULT = gamma.SetReGammaRampMemory(gamma_ramp_data)
#         assert ret_set == ADLX.ADLX_RESULT.ADLX_OK

#     # currently in unit tests we have one thread, let's give callback some time to execute
#     time.sleep(4)


def test_remove_display_gamma_event_listener_gamma(adlx):
    """Test Gamma events RemoveDisplayGammaEventListener()"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    display_service: ADLX.IADLXDisplayServices = system.GetDisplaysServices()

    display_change_handler: ADLX.IADLXDisplayChangedHandling = display_service.GetDisplayChangedHandling()

    callback: ADLX.PyDisplayGammaChangedListenerCallback = ADLX.PyDisplayGammaChangedListenerCallback()
    callback.call = callback_display_gamma_changed

    res_add_gamma_listener: ADLX.ADLX_RESULT = display_change_handler.AddDisplayGammaEventListener(callback)
    assert res_add_gamma_listener == ADLX.ADLX_RESULT.ADLX_OK

    res_remove_gamma_listener: ADLX.ADLX_RESULT = display_change_handler.RemoveDisplayGammaEventListener(callback)
    assert res_remove_gamma_listener == ADLX.ADLX_RESULT.ADLX_OK
    del callback, display_change_handler, display_service, system
