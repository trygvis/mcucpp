#pragma once

// TODO: Include the platform specific includes here like core_x.h so that they most likely will define __unused etc.

#ifndef __unused

#if defined(__GNUC__)
#define __unused __attribute__((unused))
#else
#define __unused
#endif

#ifndef __always_inline
#define __always_inline
#endif

#endif
