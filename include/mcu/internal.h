#pragma once

// TODO: Include the platform specific includes here like core_x.h so that they most likely will define __unused etc.

#ifndef __unused

#if defined(__GNUC__)
#define __unused __attribute__((unused))
#else
#define __unused
#endif

#endif // __unused

#ifndef __always_inline

#if defined(__GNUC__)
#define __always_inline __attribute__((always_inline))
#else
#define __always_inline
#endif

#endif // __always_inline

#ifndef __noinline

#if defined(__GNUC__)
#define __noinline __attribute__((noinline))
#else
#define __noinline
#endif

#endif // __noinline
