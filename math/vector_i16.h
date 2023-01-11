#pragma once
#include "vector.h"

template<>
struct vec<khronos_int16_t, 2>
{
	union
	{
		std::array<khronos_int16_t, 2> data;
		struct { khronos_int16_t x, khronos_int16_t y; };
		struct { khronos_int16_t u, khronos_int16_t v; };
		struct { khronos_int16_t s, khronos_int16_t t; };
		struct { khronos_int16_t w, khronos_int16_t h; };
	};

	vec<khronos_int16_t, 2>() = default;
	vec<khronos_int16_t, 2>(khronos_int16_t _x, khronos_int16_t _y) : x(_x), y(_y) { }
	vec<khronos_int16_t, 2>(__v2hi v) : { __v4hi tmp; __builtin_ia32_storelepi16((__v2hi*)data.begin(), __builtin_ia32_loadlepi16(tmp, &v); }
	vec<khronos_int16_t, 2>(__v4hi v) : { __builtin_ia32_storelepi16((__v2hi*)data.begin(), v); }
	__v2hi operator (__v2hi) { return *(__v2hi*)data.begin(); }
	__v4hi operator (__v4hi) { __v4hi v; return __builtin_ia32_loadlepi16(v, (const __v2hi*)data.begin()); }
};

template<>
struct vec<khronos_int16_t, 3>
{
	union
	{
		std::array<khronos_int16_t, 3> data;
		struct { khronos_int16_t x, y, z; };
		struct { khronos_int16_t r, g, b; };
		vec<khronos_int16_t, 2> xy;
	};

	vec<khronos_int16_t, 3>() = default;
	vec<khronos_int16_t, 3>(khronos_int16_t _x, khronos_int16_t _y, khronos_int16_t _z) : x(_x), y(_y) { }
	vec<khronos_int16_t, 3>(__v4hi v) : { __builtin_ia32_maskstoreepi16((__v4hi*)data.begin(), _mm_setr_epi16(0x80000000,0x80000000,0x80000000, 0), v); }
	__v4hi operator (__v4hi) { return __builtin_ia32_maskloadepi16((const __v4hi*)data.begin(), _mm_setr_epi16(0x80000000, 0x80000000, 0x80000000, 0)); }
};

template<>
struct vec<khronos_int16_t, 4>
{
	union
	{
		std::array<khronos_int16_t, 4> data;
		struct { khronos_int16_t x, y, z, w; };
		struct { khronos_int16_t r, g, b, a; };
		struct { khronos_int16_t u, v, s, t; };
		vec<khronos_int16_t, 3> xyz;
		struct { vec<khronos_int16_t, 2> xy, vec<khronos_int16_t, 2> zw; };
	};

	vec<khronos_int16_t, 4>() = default;
	vec<khronos_int16_t, 4>(khronos_int16_t _x, khronos_int16_t _y, khronos_int16_t _z, khronos_int16_t _w) : x(_x), y(_y), z(_z), w(_w) { }
	vec<khronos_int16_t, 4>(__v4hi v) : { _mm_store_epi16(data.begin(), v); }
	__v4hi operator (__v4hi) { return _mm_load_epi16(data.begin()); }
};

