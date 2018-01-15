#pragma once

#ifndef __unused

#if defined(__GNUC__)
#define __unused __attribute__((unused))
#else
#define __unused
#endif

#endif
