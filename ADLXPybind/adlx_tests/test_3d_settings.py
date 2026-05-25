#
# Copyright Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------

""" Module for 3D settings tests """
import pytest

from typing import Dict, List

try:
    import ADLX
except ImportError:
    from adlx import ADLX


def is_feature_supported(interface) -> bool:
    """Helper function to check if feature is supported.
    
    Args:
        interface: The ADLX interface object to check
    
    Returns:
        bool: True if supported, False otherwise
    """
    if not hasattr(interface, 'IsSupported'):
        return False
    
    is_supported = interface.IsSupported()
    assert isinstance(is_supported, bool), f"IsSupported() should return a bool, got {type(is_supported)}"
    if not is_supported:
        print(f"Feature not supported")
    return is_supported


@pytest.mark.parametrize(
    "method,mtype",
    [
        ("GetLevel", ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL),
        ("IsEnabled", bool),
        ("IsSupported", bool),
    ],
)
def test_3D_anisotropic_filtering_apis(adlx, method, mtype):
    """Check if 3DAnisotropicFiltering methods return non empty objects."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()

    assert len(gpus) > 0

    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        af: ADLX.IADLX3DAnisotropicFiltering = three_d_settings_services.GetAnisotropicFiltering(gpu)
        if not is_feature_supported(af):
            continue
        param = getattr(af, method)()
        if mtype is bool:
            assert isinstance(param, mtype)
        else:
            assert param
            assert isinstance(param, mtype)


@pytest.mark.parametrize("bool_value", [True, False])
def test_set_enable_anisotropic_filtering(adlx, bool_value):
    """Call SetEnabled() on IADLX3DAnisotropicFiltering interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        af: ADLX.IADLX3DAnisotropicFiltering = three_d_settings_services.GetAnisotropicFiltering(gpu)
        if not is_feature_supported(af):
            continue
        ret_set_enabled: ADLX.ADLX_RESULT = af.SetEnabled(bool_value)
        assert isinstance(ret_set_enabled, ADLX.ADLX_RESULT)
        assert ret_set_enabled == ADLX.ADLX_RESULT.ADLX_OK


@pytest.mark.parametrize(
    "filtering_level,exit_code",
    [
        (
            ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_INVALID,
            [ADLX.ADLX_RESULT.ADLX_INVALID_ARGS],
        ),
        (
            ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X2,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED],
        ),
        (
            ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X4,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED],
        ),
        (
            ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X8,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED],
        ),
        (
            ADLX.ADLX_ANISOTROPIC_FILTERING_LEVEL.AF_LEVEL_X16,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED],
        ),
    ],
)
def test_set_level_anisotropic_filtering(adlx, filtering_level, exit_code):
    """Call SetLevel() on IADLX3DAnisotropicFiltering interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        af: ADLX.IADLX3DAnisotropicFiltering = three_d_settings_services.GetAnisotropicFiltering(gpu)
        if not is_feature_supported(af):
            continue
        ret_set_level: ADLX.ADLX_RESULT = af.SetLevel(filtering_level)
        assert isinstance(ret_set_level, ADLX.ADLX_RESULT)
        assert ret_set_level in exit_code


def test_is_anti_aliasing_supported(adlx):
    """Call IsSupported() on IADLX3DAntiAliasing interface. Expect bool return value"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        aa: ADLX.IADLX3DAntiAliasing = three_d_settings_services.GetAntiAliasing(gpu)
        ret_aa: bool = aa.IsSupported()
        assert isinstance(ret_aa, bool)


@pytest.mark.parametrize(
    # fmt: off
    "set_method,get_method,aa_enum_type,aa_enum,return_value",
    [
        ("SetLevel", "GetLevel", ADLX.ADLX_ANTI_ALIASING_LEVEL, ADLX.ADLX_ANTI_ALIASING_LEVEL.AA_LEVEL_INVALID,[ADLX.ADLX_RESULT.ADLX_INVALID_ARGS]),
        ("SetLevel", "GetLevel", ADLX.ADLX_ANTI_ALIASING_LEVEL, ADLX.ADLX_ANTI_ALIASING_LEVEL.AA_LEVEL_2X ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_ANTI_ALIASING_LEVEL, ADLX.ADLX_ANTI_ALIASING_LEVEL.AA_LEVEL_2XEQ ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_ANTI_ALIASING_LEVEL, ADLX.ADLX_ANTI_ALIASING_LEVEL.AA_LEVEL_4X ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_ANTI_ALIASING_LEVEL, ADLX.ADLX_ANTI_ALIASING_LEVEL.AA_LEVEL_4XEQ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_ANTI_ALIASING_LEVEL, ADLX.ADLX_ANTI_ALIASING_LEVEL.AA_LEVEL_8X ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_ANTI_ALIASING_LEVEL, ADLX.ADLX_ANTI_ALIASING_LEVEL.AA_LEVEL_8XEQ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),

        ("SetMethod", "GetMethod", ADLX.ADLX_ANTI_ALIASING_METHOD, ADLX.ADLX_ANTI_ALIASING_METHOD.AA_METHOD_MULTISAMPLING,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMethod", "GetMethod", ADLX.ADLX_ANTI_ALIASING_METHOD, ADLX.ADLX_ANTI_ALIASING_METHOD.AA_METHOD_ADAPTIVE_MULTISAMPLING  ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMethod", "GetMethod", ADLX.ADLX_ANTI_ALIASING_METHOD, ADLX.ADLX_ANTI_ALIASING_METHOD.AA_METHOD_SUPERSAMPLING ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),

        ("SetMode", "GetMode", ADLX.ADLX_ANTI_ALIASING_MODE, ADLX.ADLX_ANTI_ALIASING_MODE.AA_MODE_USE_APP_SETTINGS ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMode", "GetMode", ADLX.ADLX_ANTI_ALIASING_MODE, ADLX.ADLX_ANTI_ALIASING_MODE.AA_MODE_ENHANCE_APP_SETTINGS   ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMode", "GetMode", ADLX.ADLX_ANTI_ALIASING_MODE, ADLX.ADLX_ANTI_ALIASING_MODE.AA_MODE_OVERRIDE_APP_SETTINGS  ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
    ],
    # fmt: on
)
def test_anti_aliasing_set_get_methods(adlx, set_method, get_method, aa_enum_type, aa_enum, return_value):
    """Call SetLevel/GetLevel, SetMethod/GetMethod, SetMode/GetMode on IADLX3DAntiAliasing interaface.
    Try all combinations"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        aa: ADLX.IADLX3DAntiAliasing = three_d_settings_services.GetAntiAliasing(gpu)
        if not is_feature_supported(aa):
            continue
        param = getattr(aa, set_method)(aa_enum)
        assert isinstance(param, ADLX.ADLX_RESULT)
        assert param in return_value

        param2 = getattr(aa, get_method)()
        assert isinstance(param2, aa_enum_type)


def test_is_enabled_anti_lag(adlx):
    """Call IsEnabled() on IADLX3DAntiLag interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        al: ADLX.IADLX3DAntiLag = three_d_settings_services.GetAntiLag(gpu)
        if not is_feature_supported(al):
            continue
        is_enabled_anti_lag: bool = al.IsEnabled()
        assert isinstance(is_enabled_anti_lag, bool)


def test_is_supported_anti_lag(adlx):
    """Call IsSupported() on IADLX3DAntiLag interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        al: ADLX.IADLX3DAntiLag = three_d_settings_services.GetAntiLag(gpu)
        is_supported_anti_lag: bool = al.IsSupported()
        assert isinstance(is_supported_anti_lag, bool)

def test_get_level_anti_lag(adlx):
    """Call GetLevel() on IADLX3DAntiLag interface. Expect int response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        al: ADLX.IADLX3DAntiLag = three_d_settings_services.GetAntiLag(gpu)
        if not is_feature_supported(al):
            continue
        antiLagLevel: ADLX.ADLX_ANTILAG_STATE = al.GetLevel()
        if antiLagLevel:
            assert isinstance(antiLagLevel, ADLX.ADLX_ANTILAG_STATE)

@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_anti_lag(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DAntiLag interface. Expect ADLX_RESULT response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        al: ADLX.IADLX3DAntiLag = three_d_settings_services.GetAntiLag(gpu)
        if not is_feature_supported(al):
            continue
        set_enable_anti_lag: ADLX.ADLX_RESULT = al.SetEnabled(adlx_bool)
        assert isinstance(set_enable_anti_lag, ADLX.ADLX_RESULT)
        assert (
            set_enable_anti_lag == ADLX.ADLX_RESULT.ADLX_OK
            or set_enable_anti_lag == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED
        )


def test_get_resolution_3d_boost(adlx):
    """Call GetResolution() on IADLX3DBoost interface. Expect int response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        if not is_feature_supported(boost):
            continue
        resolution: int = boost.GetResolution()
        assert resolution
        assert isinstance(resolution, int)


def test_get_resolution_range_3d_boost(adlx):
    """Call GetResolutionRange() on IADLX3DBoost interface. Expect dict response with keys: maxValue, minValue, step."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        if not is_feature_supported(boost):
            continue
        res_range: Dict[str, int] = boost.GetResolutionRange()
        assert res_range
        assert isinstance(res_range["maxValue"], int)
        assert isinstance(res_range["minValue"], int)
        assert isinstance(res_range["step"], int)


def test_is_enabled_3d_boost(adlx):
    """Call IsEnabled() on IADLX3DBoost interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        if not is_feature_supported(boost):
            continue
        is_enabled: bool = boost.IsEnabled()
        assert isinstance(is_enabled, bool)


def test_is_supported_3d_boost(adlx):
    """Call IsSupported() on IADLX3DBoost interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        is_supported: bool = boost.IsSupported()
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_3d_boost(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DBoost interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        if not is_feature_supported(boost):
            continue
        set_enabled: ADLX.ADLX_RESULT = boost.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK

        if adlx_bool:
            assert boost.IsEnabled()
        if not adlx_bool:
            assert not boost.IsEnabled()


def test_set_resolution_3d_boost(adlx):
    """Call SetResolution() on IADLX3DBoost interface. Expect ADLX.ADLX_RESULT response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        if not is_feature_supported(boost):
            continue
        res_range: Dict[str, int] = boost.GetResolutionRange()
        res_to_set: int = round(res_range["minValue"] + (res_range["step"] / 2))

        set_enabled: ADLX.ADLX_RESULT = boost.SetEnabled(True)
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK

        set_res: ADLX.ADLX_RESULT = boost.SetResolution(res_to_set)
        assert set_res == ADLX.ADLX_RESULT.ADLX_OK


def test_negative_set_resolution_3d_boost(adlx):
    """Call SetResolution() on IADLX3DBoost interface. Expect ADLX.ADLX_RESULT response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        boost: ADLX.IADLX3DBoost = three_d_settings_services.GetBoost(gpu)
        if not is_feature_supported(boost):
            continue
        res_range: Dict[str, int] = boost.GetResolutionRange()

        set_enabled: ADLX.ADLX_RESULT = boost.SetEnabled(True)
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK

        set_res: ADLX.ADLX_RESULT = boost.SetResolution(res_range["minValue"] - 1)
        assert set_res == ADLX.ADLX_RESULT.ADLX_INVALID_ARGS

        set_res: ADLX.ADLX_RESULT = boost.SetResolution(res_range["maxValue"] + 1)
        assert set_res == ADLX.ADLX_RESULT.ADLX_INVALID_ARGS

def test_get_fps_range_chill(adlx):
    """Call GetFPSRange() on IADLX3DChill interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        if not is_feature_supported(chill):
            continue
        res_range: Dict[str, int] = chill.GetFPSRange()
        assert res_range
        assert isinstance(res_range["maxValue"], int)
        assert isinstance(res_range["minValue"], int)
        assert isinstance(res_range["step"], int)


def test_get_max_fps_chill(adlx):
    """Call GetMaxFPS() on IADLX3DChill interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        if not is_feature_supported(chill):
            continue
        max_fps: int = chill.GetMaxFPS()
        assert isinstance(max_fps, int)


def test_get_min_fps_chill(adlx):
    """Call GetMinFPS() on IADLX3DChill interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        if not is_feature_supported(chill):
            continue
        min_fps: int = chill.GetMinFPS()
        assert isinstance(min_fps, int)


def test_is_enabled_chill(adlx):
    """Call IsEnabled() on IADLX3DChill interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        if not is_feature_supported(chill):
            continue
        is_enabled: bool = chill.IsEnabled()
        assert isinstance(is_enabled, bool)


def test_is_supported_chill(adlx):
    """Call IsSupported() on IADLX3DChill interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        is_supported: bool = chill.IsSupported()
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_chill(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DChill interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        if not is_feature_supported(chill):
            continue
        set_enabled: ADLX.ADLX_RESULT = chill.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK or set_enabled == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED

        if adlx_bool:
            assert chill.IsEnabled()
        if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            assert not chill.IsEnabled()


def test_set_max_fps_chill(adlx):
    """Call SetMaxFPS() on IADLX3DChill interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        if not is_feature_supported(chill):
            continue
        res_range: Dict[str, int] = chill.GetFPSRange()
        new_max: int = res_range["maxValue"] + 1

        ret_set_max_fps: ADLX.ADLX_RESULT = chill.SetMaxFPS(new_max)
        assert ret_set_max_fps in [
            ADLX.ADLX_RESULT.ADLX_OK,
            ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED,
            ADLX.ADLX_RESULT.ADLX_FAIL,
        ]
        assert isinstance(ret_set_max_fps, ADLX.ADLX_RESULT)


def test_set_min_fps_chill(adlx):
    """Call SetMinFPS() on IADLX3DChill interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        chill: ADLX.IADLX3DChill = three_d_settings_services.GetChill(gpu)
        if not is_feature_supported(chill):
            continue
        res_range: Dict[str, int] = chill.GetFPSRange()
        new_min: int = res_range["minValue"] - 1

        ret_set_max_fps: ADLX.ADLX_RESULT = chill.SetMinFPS(new_min)
        assert ret_set_max_fps in [
            ADLX.ADLX_RESULT.ADLX_OK,
            ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED,
            ADLX.ADLX_RESULT.ADLX_FAIL,
        ]
        assert isinstance(ret_set_max_fps, ADLX.ADLX_RESULT)


def test_is_enabled_enhanced_sync(adlx):
    """Call IsEnabled() on IADLX3DEnhancedSync interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        enhanced_sync: ADLX.IADLX3DEnhancedSync = three_d_settings_services.GetEnhancedSync(gpu)
        if not is_feature_supported(enhanced_sync):
            continue
        is_enabled: bool = enhanced_sync.IsEnabled()
        assert isinstance(is_enabled, bool)


def test_is_supported_enhanced_sync(adlx):
    """Call IsSupported() on IADLX3DEnhancedSync interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        enhanced_sync: ADLX.IADLX3DEnhancedSync = three_d_settings_services.GetEnhancedSync(gpu)
        is_supported: bool = enhanced_sync.IsSupported()
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_enhanced_sync(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DEnhancedSync interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        enhanced_sync: ADLX.IADLX3DEnhancedSync = three_d_settings_services.GetEnhancedSync(gpu)
        if not is_feature_supported(enhanced_sync):
            continue
        ret_set_enableis_supported: ADLX.ADLX_RESULT = enhanced_sync.SetEnabled(adlx_bool)
        assert isinstance(ret_set_enableis_supported, ADLX.ADLX_RESULT)

        if adlx_bool:
            assert enhanced_sync.IsEnabled()
        if not adlx_bool and ret_set_enableis_supported == ADLX.ADLX_RESULT.ADLX_OK:
            assert not enhanced_sync.IsEnabled()


def test_get_fps_frame_rate_tc(adlx):
    """Call GetFPS() on IADLX3DFrameRateTargetControl interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_rate_tc: ADLX.IADLX3DFrameRateTargetControl = three_d_settings_services.GetFrameRateTargetControl(gpu)
        if not is_feature_supported(frame_rate_tc):
            continue
        curr_fps: int = frame_rate_tc.GetFPS()
        assert isinstance(curr_fps, int)


def test_get_fps_range_frame_rate_tc(adlx):
    """Call GetFPSRange() on IADLX3DFrameRateTargetControl interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_rate_tc: ADLX.IADLX3DFrameRateTargetControl = three_d_settings_services.GetFrameRateTargetControl(gpu)
        if not is_feature_supported(frame_rate_tc):
            continue
        res_range: Dict[str, int] = frame_rate_tc.GetFPSRange()
        assert res_range
        assert isinstance(res_range["maxValue"], int)
        assert isinstance(res_range["minValue"], int)
        assert isinstance(res_range["step"], int)


def test_is_enabled_range_frame_rate_tc(adlx):
    """Call IsEnabled() on IADLX3DFrameRateTargetControl interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_rate_tc: ADLX.IADLX3DFrameRateTargetControl = three_d_settings_services.GetFrameRateTargetControl(gpu)
        if not is_feature_supported(frame_rate_tc):
            continue
        is_enabled: bool = frame_rate_tc.IsEnabled()
        assert isinstance(is_enabled, bool)


def test_is_supported_range_frame_rate_tc(adlx):
    """Call IsSupported() on IADLX3DFrameRateTargetControl interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_rate_tc: ADLX.IADLX3DFrameRateTargetControl = three_d_settings_services.GetFrameRateTargetControl(gpu)
        is_supported: bool = frame_rate_tc.IsSupported()
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_range_frame_rate_tc(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DFrameRateTargetControl interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_rate_tc: ADLX.IADLX3DFrameRateTargetControl = three_d_settings_services.GetFrameRateTargetControl(gpu)
        if not is_feature_supported(frame_rate_tc):
            continue
        set_enabled: ADLX.ADLX_RESULT = frame_rate_tc.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK or set_enabled == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED

        if adlx_bool:
            assert frame_rate_tc.IsEnabled()
        if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            assert not frame_rate_tc.IsEnabled()


def test_get_sharpness_image_sharpening(adlx):
    """Call GetSharpness() on IADLX3DImageSharpening interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpening: ADLX.IADLX3DImageSharpening = three_d_settings_services.GetImageSharpening(gpu)
        if not is_feature_supported(image_sharpening):
            continue
        sharpness: int = image_sharpening.GetSharpness()
        assert isinstance(sharpness, int)


def test_get_sharpness_range_image_sharpening(adlx):
    """Call GetSharpnessRange() on IADLX3DImageSharpening interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpening: ADLX.IADLX3DImageSharpening = three_d_settings_services.GetImageSharpening(gpu)
        if not is_feature_supported(image_sharpening):
            continue
        res_range: Dict[str, int] = image_sharpening.GetSharpnessRange()
        assert res_range
        assert isinstance(res_range["maxValue"], int)
        assert isinstance(res_range["minValue"], int)
        assert isinstance(res_range["step"], int)


def test_is_enabled_image_sharpening(adlx):
    """Call IsEnabled() on IADLX3DImageSharpening interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpening: ADLX.IADLX3DImageSharpening = three_d_settings_services.GetImageSharpening(gpu)
        if not is_feature_supported(image_sharpening):
            continue
        is_enabled: bool = image_sharpening.IsEnabled()
        assert isinstance(is_enabled, bool)


def test_is_supported_image_sharpening(adlx):
    """Call IsSupported() on IADLX3DImageSharpening interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpening: ADLX.IADLX3DImageSharpening = three_d_settings_services.GetImageSharpening(gpu)
        is_supported: bool = image_sharpening.IsSupported()
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_image_sharpening(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DImageSharpening interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpening: ADLX.IADLX3DImageSharpening = three_d_settings_services.GetImageSharpening(gpu)
        if not is_feature_supported(image_sharpening):
            continue
        set_enabled: ADLX.ADLX_RESULT = image_sharpening.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK or set_enabled == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED

        if adlx_bool:
            assert image_sharpening.IsEnabled()
        if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            assert not image_sharpening.IsEnabled()


def test_set_sharpness_image_sharpening(adlx):
    """Call SetSharpness() on IADLX3DImageSharpening interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpening: ADLX.IADLX3DImageSharpening = three_d_settings_services.GetImageSharpening(gpu)
        if not is_feature_supported(image_sharpening):
            continue
        res_range: Dict[str, int] = image_sharpening.GetSharpnessRange()
        new_value: int = res_range["maxValue"] + 1

        ret_set_sharpness: ADLX.ADLX_RESULT = image_sharpening.SetSharpness(new_value)
        assert ret_set_sharpness in [
            ADLX.ADLX_RESULT.ADLX_OK,
            ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED,
            ADLX.ADLX_RESULT.ADLX_FAIL,
        ]
        assert isinstance(ret_set_sharpness, ADLX.ADLX_RESULT)


def test_is_enabled_image_sharpen_desktop(adlx):
    """Call IsEnabled() on IADLX3DImageSharpenDesktop interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpen_desktop: ADLX.IADLX3DImageSharpenDesktop = three_d_settings_services.GetImageSharpenDesktop(gpu)
        if not is_feature_supported(image_sharpen_desktop):
            continue
        is_enabled: bool = image_sharpen_desktop.IsEnabled()
        if is_enabled is not None:
            assert isinstance(is_enabled, bool)


def test_is_supported_image_sharpen_desktop(adlx):
    """Call IsSupported() on IADLX3DImageSharpenDesktop interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpen_desktop: ADLX.IADLX3DImageSharpenDesktop = three_d_settings_services.GetImageSharpenDesktop(gpu)
        is_supported: bool = image_sharpen_desktop.IsSupported()
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_image_sharpen_desktop(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DImageSharpenDesktop interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        image_sharpen_desktop: ADLX.IADLX3DImageSharpenDesktop = three_d_settings_services.GetImageSharpenDesktop(gpu)
        if not is_feature_supported(image_sharpen_desktop):
            continue
        set_enabled: ADLX.ADLX_RESULT = image_sharpen_desktop.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        if set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            if adlx_bool:
                assert image_sharpen_desktop.IsEnabled()
            if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
                assert not image_sharpen_desktop.IsEnabled()

def test_is_enabled_FSR(adlx):
    """Call IsEnabled() on IADLX3DFidelityFXSuperResolution interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        fsr: ADLX.IADLX3DFidelityFXSuperResolution = three_d_settings_services.GetFidelityFXSuperResolution(gpu)
        if not is_feature_supported(fsr):
            continue
        is_enabled: bool = fsr.IsEnabled()
        if is_enabled is not None:
            assert isinstance(is_enabled, bool)


def test_is_supported_FSR(adlx):
    """Call IsSupported() on IADLX3DFidelityFXSuperResolution interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        fsr: ADLX.IADLX3DFidelityFXSuperResolution = three_d_settings_services.GetFidelityFXSuperResolution(gpu)
        is_supported: bool = fsr.IsSupported()
        assert isinstance(is_supported, bool)

@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_FSR(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DFidelityFXSuperResolution interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        fsr: ADLX.IADLX3DFidelityFXSuperResolution = three_d_settings_services.GetFidelityFXSuperResolution(gpu)
        if not is_feature_supported(fsr):
            continue
        set_enabled: ADLX.ADLX_RESULT = fsr.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        if set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            if adlx_bool:
                assert fsr.IsEnabled()
            if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
                assert not fsr.IsEnabled()

def test_is_supported_FrameGenUpgrade(adlx):
    """Call IsSupported() on IADLX3DFidelityFXFrameGenUpgrade interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_gen: ADLX.IADLX3DFidelityFXFrameGenUpgrade = three_d_settings_services.GetFidelityFXFrameGenUpgrade(gpu)
        is_supported: bool = frame_gen.IsSupported()
        assert isinstance(is_supported, bool)

def test_is_enabled_FrameGenUpgrade(adlx):
    """Call IsEnabled() on IADLX3DFidelityFXFrameGenUpgrade interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_gen: ADLX.IADLX3DFidelityFXFrameGenUpgrade = three_d_settings_services.GetFidelityFXFrameGenUpgrade(gpu)
        if not is_feature_supported(frame_gen):
            continue
        is_enabled: bool = frame_gen.IsEnabled()
        if is_enabled is not None:
            assert isinstance(is_enabled, bool)

@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_FrameGenUpgrade(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DFidelityFXFrameGenUpgrade interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        frame_gen: ADLX.IADLX3DFidelityFXFrameGenUpgrade = three_d_settings_services.GetFidelityFXFrameGenUpgrade(gpu)
        if not is_feature_supported(frame_gen):
            continue
        set_enabled: ADLX.ADLX_RESULT = frame_gen.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        if set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            if adlx_bool:
                assert frame_gen.IsEnabled()
            if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
                assert not frame_gen.IsEnabled()

def test_is_enabled_morphological_aa(adlx):
    """Call IsEnabled() on IADLX3DMorphologicalAntiAliasing interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        morphological_aa: ADLX.IADLX3DMorphologicalAntiAliasing = (
            three_d_settings_services.GetMorphologicalAntiAliasing(gpu)
        )
        if not is_feature_supported(morphological_aa):
            continue
        is_enabled: bool = morphological_aa.IsEnabled()
        assert isinstance(is_enabled, bool)


def test_is_supported_morphological_aa(adlx):
    """Call IsSupported() on IADLX3DMorphologicalAntiAliasing interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        morphological_aa: ADLX.IADLX3DMorphologicalAntiAliasing = (
            three_d_settings_services.GetMorphologicalAntiAliasing(gpu)
        )
        is_supported: bool = morphological_aa.IsSupported()
        assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_morphological_aa(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DMorphologicalAntiAliasing interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        morphological_aa: ADLX.IADLX3DMorphologicalAntiAliasing = (
            three_d_settings_services.GetMorphologicalAntiAliasing(gpu)
        )
        if not is_feature_supported(morphological_aa):
            continue
        set_enabled: ADLX.ADLX_RESULT = morphological_aa.SetEnabled(adlx_bool)
        assert set_enabled
        assert isinstance(set_enabled, ADLX.ADLX_RESULT)
        assert set_enabled == ADLX.ADLX_RESULT.ADLX_OK or set_enabled == ADLX.ADLX_RESULT.ADLX_NOT_SUPPORTED

        if adlx_bool:
            assert morphological_aa.IsEnabled()
        if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
            assert not morphological_aa.IsEnabled()


# ---------------------------------------------------------------------------------------------


##################
def test_get_sharpness_rsr(adlx):
    """Call GetSharpness() on IADLX3DRadeonSuperResolution interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    if not is_feature_supported(rsr):
        return
    current_sharpness: int = rsr.GetSharpness()
    assert isinstance(current_sharpness, int)


def test_get_sharpness_rsr(adlx):
    """Call GetSharpnessRange() on IADLX3DRadeonSuperResolution interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    if not is_feature_supported(rsr):
        return
    res_range: Dict[str, int] = rsr.GetSharpnessRange()
    assert res_range
    assert isinstance(res_range["maxValue"], int)
    assert isinstance(res_range["minValue"], int)
    assert isinstance(res_range["step"], int)


def test_is_enabled_rsr(adlx):
    """Call IsEnabled() on IADLX3DRadeonSuperResolution interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    if not is_feature_supported(rsr):
        return
    is_enabled: bool = rsr.IsEnabled()
    assert isinstance(is_enabled, bool)


def test_is_supported_rsr(adlx):
    """Call IsSupported() on IADLX3DRadeonSuperResolution interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    is_supported: bool = rsr.IsSupported()
    assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_rsr(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DRadeonSuperResolution interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    if not is_feature_supported(rsr):
        return
    set_enabled: ADLX.ADLX_RESULT = rsr.SetEnabled(adlx_bool)
    assert set_enabled
    assert isinstance(set_enabled, ADLX.ADLX_RESULT)

    if adlx_bool:
        assert rsr.IsEnabled()
    if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
        assert not rsr.IsEnabled()


def test_set_sharpness_rsr(adlx):
    """Call SetSharpness() on IADLX3DRadeonSuperResolution interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    rsr: ADLX.IADLX3DRadeonSuperResolution = three_d_settings_services.GetRadeonSuperResolution()
    if not is_feature_supported(rsr):
        return
    res_range: Dict[str, int] = rsr.GetSharpnessRange()

    set_enabled: ADLX.ADLX_RESULT = rsr.SetSharpness(round(res_range["step"] / 2))
    assert set_enabled
    assert isinstance(set_enabled, ADLX.ADLX_RESULT)


def test_is_supported_shader_cache(adlx):
    """Call IsSupported() on IADLX3DResetShaderCache interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        shader_cache: ADLX.IADLX3DResetShaderCache = three_d_settings_services.GetResetShaderCache(gpu)
        is_supported: bool = shader_cache.IsSupported()
        assert is_supported
        assert isinstance(is_supported, bool)


def test_reset_shader_cache(adlx):
    """Call ResetShaderCache() on IADLX3DResetShaderCache interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        shader_cache: ADLX.IADLX3DResetShaderCache = three_d_settings_services.GetResetShaderCache(gpu)
        if not is_feature_supported(shader_cache):
            continue
        ret_reset_shader_cache: ADLX.ADLX_RESULT = shader_cache.ResetShaderCache()
        assert ret_reset_shader_cache
        assert isinstance(ret_reset_shader_cache, ADLX.ADLX_RESULT)


@pytest.mark.parametrize(
    # fmt: off
    "set_method,get_method,aa_enum_type,aa_enum,return_value",
    [
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_OFF,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_INVALID_ARGS]),
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_2X,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_4X,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_6X,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_8X,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_16X,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_32X,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetLevel", "GetLevel", ADLX.ADLX_TESSELLATION_LEVEL, ADLX.ADLX_TESSELLATION_LEVEL.T_LEVEL_64X,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),

        ("SetMode", "GetMode", ADLX.ADLX_TESSELLATION_MODE, ADLX.ADLX_TESSELLATION_MODE.T_MODE_AMD_OPTIMIZED ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMode", "GetMode", ADLX.ADLX_TESSELLATION_MODE, ADLX.ADLX_TESSELLATION_MODE.T_MODE_USE_APP_SETTINGS   ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMode", "GetMode", ADLX.ADLX_TESSELLATION_MODE, ADLX.ADLX_TESSELLATION_MODE.T_MODE_OVERRIDE_APP_SETTINGS  ,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
    ],
    # fmt: on
)
def test_set_get_methods_tessellation(adlx, set_method, get_method, aa_enum_type, aa_enum, return_value):
    """Call SetLevel/GetLevel, SetMode/GetMode on IADLX3DTessellation interaface.
    Try all combinations"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tessellation: ADLX.IADLX3DTessellation = three_d_settings_services.GetTessellation(gpu)
        if not is_feature_supported(tessellation):
            continue
        param = getattr(tessellation, set_method)(aa_enum)
        assert isinstance(param, ADLX.ADLX_RESULT)
        assert param in return_value

        param2 = getattr(tessellation, get_method)()
        assert isinstance(param2, aa_enum_type)


def test_is_supported_tessellation(adlx):
    """Call IsSupported  interface. Expect bool return value"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        tessellation: ADLX.IADLX3DTessellation = three_d_settings_services.GetTessellation(gpu)
        is_supported: bool = tessellation.IsSupported()
        assert isinstance(is_supported, bool)

def test_is_supported_WaitForVerticalRefresh(adlx):
    """Call IsSupported  interface. Expect bool return value"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        wait_for_vertical_refresh: ADLX.IADLX3DWaitForVerticalRefresh = three_d_settings_services.GetWaitForVerticalRefresh(gpu)
        is_supported: bool = wait_for_vertical_refresh.IsSupported()
        assert isinstance(is_supported, bool)

@pytest.mark.parametrize(
    # fmt: off
    "set_method,get_method,aa_enum_type,aa_enum,return_value",
    [
        ("SetMode", "GetMode", ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE, ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE.WFVR_ALWAYS_OFF,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMode", "GetMode", ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE, ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE.WFVR_OFF_UNLESS_APP_SPECIFIES,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMode", "GetMode", ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE, ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE.WFVR_ON_UNLESS_APP_SPECIFIES,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
        ("SetMode", "GetMode", ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE, ADLX.ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE.WFVR_ALWAYS_ON,[ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_FAIL]),
    ],
    # fmt: on
)
def test_set_get_methods_WaitForVerticalRefresh(adlx, set_method, get_method, aa_enum_type, aa_enum, return_value):
    """SetMode/GetMode on IADLX3DWaitForVerticalRefresh interaface.
    Try all combinations"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    gpus: List[ADLX.IADLXGPU] = system.GetGPUs()
    for gpu in gpus:
        if gpu.Type() == ADLX.ADLX_GPU_TYPE.GPUTYPE_UNDEFINED:
            continue
        wait_for_vertical_refresh: ADLX.IADLX3DWaitForVerticalRefresh = (
            three_d_settings_services.GetWaitForVerticalRefresh(gpu)
        )
        if not is_feature_supported(wait_for_vertical_refresh):
            continue
        param = getattr(wait_for_vertical_refresh, set_method)(aa_enum)
        assert isinstance(param, ADLX.ADLX_RESULT)
        assert param in return_value

        param2 = getattr(wait_for_vertical_refresh, get_method)()
        assert isinstance(param2, aa_enum_type)


def test_is_enabled_afmf(adlx):
    """Call IsEnabled() on IADLX3DAMDFluidMotionFrames interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    is_enabled: bool = afmf.IsEnabled()
    assert isinstance(is_enabled, bool)


def test_is_supported_afmf(adlx):
    """Call IsSupported() on IADLX3DAMDFluidMotionFrames interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    is_supported: bool = afmf.IsSupported()
    assert isinstance(is_supported, bool)


@pytest.mark.parametrize("adlx_bool", [True, False])
def test_set_enabled_afmf(adlx, adlx_bool):
    """Call SetEnabled() on IADLX3DAMDFluidMotionFrames interface. Expect ADLX_RESULT response. Call IsEnabled() to check if set worked."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    set_enabled: ADLX.ADLX_RESULT = afmf.SetEnabled(adlx_bool)
    assert set_enabled
    assert isinstance(set_enabled, ADLX.ADLX_RESULT)

    if adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
        assert afmf.IsEnabled()
    if not adlx_bool and set_enabled == ADLX.ADLX_RESULT.ADLX_OK:
        assert not afmf.IsEnabled()

def test_is_supported_algorithm_afmf(adlx):
    """Call IsSupportedAlgorithm() on IADLX3DAMDFluidMotionFrames interface. Expect bool response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    is_supported: bool = afmf.IsSupportedAlgorithm()
    assert isinstance(is_supported, bool)

def test_get_algorithm_afmf(adlx):
    """Call GetAlgorithm() on IADLX3DAMDFluidMotionFrames interface. Expect ADLX_AFMF_ALGORITHM response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    if not afmf.IsSupportedAlgorithm():
        return
    algorithm: ADLX.ADLX_AFMF_ALGORITHM = afmf.GetAlgorithm()
    assert isinstance(algorithm, ADLX.ADLX_AFMF_ALGORITHM)

@pytest.mark.parametrize(
    "afmf_algorithm,exit_code",
    [
        (
            ADLX.ADLX_AFMF_ALGORITHM.AFMF_ALGORITHM_AUTO,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
        (
            ADLX.ADLX_AFMF_ALGORITHM.AFMF_ALGORITHM_ENHANCED,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
        (
            ADLX.ADLX_AFMF_ALGORITHM.AFMF_ALGORITHM_STANDARD,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
    ],
)
def test_set_algorithm_afmf(adlx, afmf_algorithm, exit_code):
    """Call SetAlgorithm() on IADLX3DAMDFluidMotionFrames interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    ret_set_enabled: ADLX.ADLX_RESULT = afmf.SetEnabled(True)
    assert isinstance(ret_set_enabled, ADLX.ADLX_RESULT)
    support_algorithm = afmf.IsSupportedAlgorithm()
    assert isinstance(support_algorithm, bool)
    if not support_algorithm:
        return
    ret_set_algorithm: ADLX.ADLX_RESULT = afmf.SetAlgorithm(afmf_algorithm)
    assert isinstance(ret_set_algorithm, ADLX.ADLX_RESULT)
    assert ret_set_algorithm in exit_code

def test_get_searchmode_afmf(adlx):
    """Call GetSearchMode() on IADLX3DAMDFluidMotionFrames interface. Expect ADLX_AFMF_SEARCH_MODE_TYPE response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    search_mode: ADLX.ADLX_AFMF_SEARCH_MODE_TYPE = afmf.GetSearchMode()
    assert isinstance(search_mode, ADLX.ADLX_AFMF_SEARCH_MODE_TYPE)

@pytest.mark.parametrize(
    "afmf_searchmode,exit_code",
    [
        (
            ADLX.ADLX_AFMF_SEARCH_MODE_TYPE.AFMF_SEARCH_MODE_AUTO,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
        (
            ADLX.ADLX_AFMF_SEARCH_MODE_TYPE.AFMF_SEARCH_MODE_STANDARD,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
        (
            ADLX.ADLX_AFMF_SEARCH_MODE_TYPE.AFMF_SEARCH_MODE_HIGH,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
    ],
)
def test_set_searchmode_afmf(adlx, afmf_searchmode, exit_code):
    """Call SetSearchMode() on IADLX3DAMDFluidMotionFrames interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    ret_set_searchmode: ADLX.ADLX_RESULT = afmf.SetSearchMode(afmf_searchmode)
    assert isinstance(ret_set_searchmode, ADLX.ADLX_RESULT)
    assert ret_set_searchmode in exit_code

def test_get_performance_mode(adlx):
    """Call GetPerformanceMode() on IADLX3DAMDFluidMotionFrames interface. Expect ADLX_AFMF_PERFORMANCE_MODE_TYPE response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    performance_mode: ADLX.ADLX_AFMF_PERFORMANCE_MODE_TYPE = afmf.GetPerformanceMode()
    assert isinstance(performance_mode, ADLX.ADLX_AFMF_PERFORMANCE_MODE_TYPE)

@pytest.mark.parametrize(
    "afmf_performance_mode,exit_code",
    [
        (
            ADLX.ADLX_AFMF_PERFORMANCE_MODE_TYPE.AFMF_PERFORMANCE_MODE_AUTO,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
        (
            ADLX.ADLX_AFMF_PERFORMANCE_MODE_TYPE.AFMF_PERFORMANCE_MODE_QUALITY,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
        (
            ADLX.ADLX_AFMF_PERFORMANCE_MODE_TYPE.AFMF_PERFORMANCE_MODE_PERFORMANCE,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
    ],
)
def test_set_performance_mode(adlx, afmf_performance_mode, exit_code):
    """Call SetPerformanceMode() on IADLX3DAMDFluidMotionFrames interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    ret_set_performance_mode: ADLX.ADLX_RESULT = afmf.SetPerformanceMode(afmf_performance_mode)
    assert isinstance(ret_set_performance_mode, ADLX.ADLX_RESULT)
    assert ret_set_performance_mode in exit_code

def test_get_fast_motion_response(adlx):
    """Call GetFastMotionResponse() on IADLX3DAMDFluidMotionFrames interface. Expect ADLX_AFMF_FAST_MOTION_RESP response."""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    fast_motion_response: ADLX.ADLX_AFMF_FAST_MOTION_RESP = afmf.GetFastMotionResponse()
    assert isinstance(fast_motion_response, ADLX.ADLX_AFMF_FAST_MOTION_RESP)

#SetFastMotionResponse
@pytest.mark.parametrize(
    "afmf_fast_motion_response,exit_code",
    [
        (
            ADLX.ADLX_AFMF_FAST_MOTION_RESP.AFMF_RESP_REPEAT_FRAMES,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
        (
            ADLX.ADLX_AFMF_FAST_MOTION_RESP.AFMF_RESP_BLENDED_FRAMES,
            [ADLX.ADLX_RESULT.ADLX_FAIL, ADLX.ADLX_RESULT.ADLX_OK, ADLX.ADLX_RESULT.ADLX_ALREADY_ENABLED, ADLX.ADLX_RESULT.ADLX_NOT_ACTIVE],
        ),
    ],
)
def test_set_fast_motion_response(adlx, afmf_fast_motion_response, exit_code):
    """Call SetFastMotionResponse() on IADLX3DAMDFluidMotionFrames interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    afmf: ADLX.IADLX3DAMDFluidMotionFrames = three_d_settings_services.GetAMDFluidMotionFrames()
    if not is_feature_supported(afmf):
        return
    ret_set_fast_motion_response: ADLX.ADLX_RESULT = afmf.SetFastMotionResponse(afmf_fast_motion_response)
    assert isinstance(ret_set_fast_motion_response, ADLX.ADLX_RESULT)
    assert ret_set_fast_motion_response in exit_code


def test_add_3d_settings_event_listenerget_3D_settings(adlx):
    """Call Add3DSettingsEventListener() on Get3DSettingsChangedHandling interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    sch: ADLX.IADLX3DSettingsChangedHandling = three_d_settings_services.Get3DSettingsChangedHandling()

    cb: ADLX.Py3DSettingsChangedListenerCallback = ADLX.Py3DSettingsChangedListenerCallback()
    add_listener: ADLX.ADLX_RESULT = sch.Add3DSettingsEventListener(cb)
    assert add_listener == ADLX.ADLX_RESULT.ADLX_OK


def test_remove_3d_settings_event_listenerget_3D_settings(adlx):
    """Call Remove3DSettingsEventListener() on Get3DSettingsChangedHandling interface"""
    system: ADLX.IADLXSystem = adlx.GetSystemServices()
    three_d_settings_services: ADLX.IADLX3DSettingsServices = system.Get3DSettingsServices()
    sch: ADLX.IADLX3DSettingsChangedHandling = three_d_settings_services.Get3DSettingsChangedHandling()

    cb: ADLX.Py3DSettingsChangedListenerCallback = ADLX.Py3DSettingsChangedListenerCallback()
    add_listener: ADLX.ADLX_RESULT = sch.Add3DSettingsEventListener(cb)
    assert add_listener == ADLX.ADLX_RESULT.ADLX_OK

    remove_listener: ADLX.ADLX_RESULT = sch.Remove3DSettingsEventListener(cb)
    assert remove_listener == ADLX.ADLX_RESULT.ADLX_OK
