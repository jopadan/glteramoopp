#pragma once

#include <cstdint>
#include <cstddef>
#include <immintrin.h>
#ifdef __SSE__ 
#include <experimental/simd>
#endif
#include <cmath>
#include <GL/glcorearb.h>
#include "fixed.h"

/* floating point scalar types */
using SCALAR 	    = GLfloat;
using SCALAR_CLAMP  = GLclampf;
using DSCALAR 	    = GLdouble;
using DSCALAR_CLAMP = GLclampd;
using INT      = khronos_int32_t;
using DWORD    = khronos_uint32_t;
using CHAR     = khronos_int8_t;
using BYTE     = khronos_uint8_t;
using SHORT    = khronos_int16_t;
using WORD     = khronos_uint16_t;
using QUAD     = khronos_int64_t;
using QWORD    = khronos_uint64_t;
using SIZE     = khronos_ssize_t;
using USIZE    = khronos_usize_t;
using TIME     = khronos_utime_nanoseconds_t;
using INT_SIZE = GLsizei;
using INT_POS  = GLint;
using SIZEPTR  = GLsizeiptr;
using INTPTR   = GLintptr;
using DWORDPTR = khronos_uintptr_t;
using TEXID    = GLuint;

/* fixed point scalar types */
using FIXEDQ16_16 = fixed<int32_t,float,16,16>;
using FIXEDQ19_8  = fixed<int32_t,float,19,8>;
using FIXEDQ32_32 = fixed<quad_t,float,32,32>;
using FIXED       = FIXEDQ16_16;

