//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Raw FFI bindings for a subset of the ADLX C interface, plus a small `ADLXHelper`
//! loader that mirrors `SDK/ADLXHelper/Windows/C/ADLXHelper.c`.
//!
//! ADLX exposes a COM-like, vtable-based C ABI. Every interface is a struct whose
//! first (and only) field is a pointer to a table of function pointers (`pVtbl`).
//! Each method takes the interface pointer as its first argument (`pThis`).
//!
//! This crate declares the interfaces and methods exercised by the ADLX Rust
//! samples, covering the system, displays, GPUs, desktops, performance monitoring,
//! 3D settings, GPU tuning, and logging services. Interfaces that are not used
//! directly are represented as opaque pointers so that the vtable layouts (and
//! therefore the method offsets) stay binary-compatible with ADLX.
//!
//! The bindings are organized into per-service submodules; every module is re-
//! exported here so consumers can keep using a flat `use amd_adlx::*`.

#![cfg(windows)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

// The C primitive types appear throughout the vtable signatures; re-exporting them
// here lets every submodule rely on `use super::*` alone.
pub use std::os::raw::{c_char, c_int, c_void};

#[macro_use]
mod macros;

mod types;
mod opaque;
mod system;
mod gpu;
mod perfmon;
mod settings3d;
mod gputuning;
mod i2c;
mod display;
mod desktop;
mod powertuning;
mod multimedia;
mod vgm;
mod helper;

pub use types::*;
pub use opaque::*;
pub use system::*;
pub use gpu::*;
pub use perfmon::*;
pub use settings3d::*;
pub use gputuning::*;
pub use i2c::*;
pub use display::*;
pub use desktop::*;
pub use powertuning::*;
pub use multimedia::*;
pub use vgm::*;
pub use helper::*;
