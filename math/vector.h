#pragma once

#include "types.h"
#include <array>

namespace math {
template<typename _Tp, size_t _Nm>
struct vec { };

template<>
struct vec<float, 2>;
template<>
struct vec<float, 3>;
template<>
struct vec<float, 4>;

template<>
struct vec<double, 2>;
template<>
struct vec<double, 3>;
template<>
struct vec<double, 4>;

template<>
struct vec<uint8_t, 2>;
template<>
struct vec<uint8_t, 3>;
template<>
struct vec<uint8_t, 4>;

template<>
struct vec<int16_t, 2>;
template<>
struct vec<int16_t, 3>;
template<>
struct vec<int16_t, 4>;

template<>
struct vec<int32_t, 2>;
template<>
struct vec<int32_t, 3>;
template<>
struct vec<int32_t, 4>;

template<>
struct vec<int64_t, 2>;
template<>
struct vec<int64_t, 3>;
template<>
struct vec<int64_t, 4>;

template<>
struct vec<FIXED, 2>;
template<>
struct vec<FIXED, 3>;
template<>
struct vec<FIXED, 4>;

#include "v2f32.h"
#include "v3f32.h"
#include "v4f32.h"
#include "v2f64.h"
#include "v3f64.h"
#include "v4f64.h"

#include "v2u8.h"
#include "v3u8.h"
#include "v4u8.h"
#include "v2i16.h"
#include "v3i16.h"
#include "v4i16.h"
#include "v2i32.h"
#include "v3i32.h"
#include "v4i32.h"
#include "v2i64.h"
#include "v3i64.h"
#include "v4i64.h"


/* floating point vector types */
using VECTOR2            = vec<float, 2>;
using VECTOR3            = vec<float, 3>;
using VECTOR4            = vec<float, 4>;
using CLAMPVECTOR2       = vec<GLclampf, 2>;
using CLAMPVECTOR3       = vec<GLclampf, 3>;
using CLAMPVECTOR4       = vec<GLclampf, 4>;
using DOUBLEVECTOR2      = vec<float, 2>;
using DOUBLEVECTOR3      = vec<float, 3>;
using DOUBLEVECTOR4      = vec<float, 4>;
using CLAMPDOUBLEVECTOR2 = vec<GLclampd, 2>;
using CLAMPDOUBLEVECTOR3 = vec<GLclampd, 3>;
using CLAMPDOUBLEVECTOR4 = vec<GLclampd, 4>;

/* integer vector types */
using QUADVECTOR2        = vec<quad_t, 2>;
using QUADVECTOR3        = vec<quad_t, 3>;
using QUADVECTOR4        = vec<quad_t, 4>;
using INTVECTOR2         = vec<int32_t, 2>;
using INTVECTOR3         = vec<int32_t, 3>;
using INTVECTOR4         = vec<int32_t, 4>;
using SHORTVECTOR2       = vec<int16_t, 2>;
using SHORTVECTOR3       = vec<int16_t, 3>;
using SHORTVECTOR4       = vec<int16_t, 4>;
using BYTEVECTOR2        = vec<uint8_t, 2>;
using BYTEVECTOR3        = vec<uint8_t, 3>;
using BYTEVECTOR4        = vec<uint8_t, 4>;

/* Q numbers fixed point vector types */
using FIXEDVECTOR2       = vec<FIXED, 2>;
using FIXEDVECTOR3       = vec<FIXED, 3>;
using FIXEDVECTOR4       = vec<FIXED, 4>;

/* default types based on the ones above */
using VECTOR      = VECTOR3;
using NORMAL      = VECTOR3;
using QUAT        = VECTOR4;
using PLANE       = VECTOR4;
using COLOR4      = VECTOR4;
using CLAMPCOLOR4 = CLAMPVECTOR4;
using SHORTVECTOR = SHORTVECTOR3;
using FIXEDVECTOR = FIXEDVECTOR3;
using COLOR4B     = BYTEVECTOR4
using COLOR       = COLOR4B;
using INTRECT     = INTVECTOR4;
using INTPOINT    = INTVECTOR2;

/* alignment of vector type */
#if ! ((defined __sun__ || defined __VXWORKS__) && defined __i386__)
#define REQUIRED_ALIGNMENT (uint8_t)(4 * sizeof(scalar) < __alignof__(max_align_t) ? 4 * sizeof(scalar) : __alignof__(max_align_t))
#else
#define REQUIRED_ALIGNMENT (uint8_t)(4 * sizeof(scalar))
#endif

};
