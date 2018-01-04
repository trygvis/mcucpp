#pragma once

#include "mcu/config.h"

#if CONFIG_CHIP_ARCH_ARM_M0
#include "core_cm0.h"
#endif

#if CONFIG_CHIP_ARCH_ARM_M3
#include "core_cm3.h"
#endif

#if CONFIG_CHIP_ARCH_ARM_M4 || CONFIG_CHIP_ARCH_ARM_M4F

#if CONFIG_CHIP_FAMILY_NRF52
#include "nrf52.h"
#endif

#include "core_cm4.h"
#endif
