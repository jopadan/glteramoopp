#pragma once
#include "vector.h"

template<>
struct vec<khronos_int32_t, 2>
{
	union
	{
		std::array<khronos_int32_t, 2> data;
		struct { khronos_int32_t x, khronos_int32_t y; };
		struct { khronos_int32_t u, khronos_int32_t v; };
		struct { khronos_int32_t s, khronos_int32_t t; };
		struct { khronos_int32_t w, khronos_int32_t h; };
	};

	vec<khronos_int32_t, 2>() = default;
	vec<khronos_int32_t, 2>(khronos_int32_t _x, khronos_int32_t _y) : x(_x), y(_y) { }
	vec<khronos_int32_t, 2>(__v2si v) : { __v4si tmp; __builtin_ia32_storelepi32((__v2si*)data.begin(), __builtin_ia32_loadlepi32(tmp, &v); }
	vec<khronos_int32_t, 2>(__v4si v) : { __builtin_ia32_storelepi32((__v2si*)data.begin(), v); }
	__v2si operator (__v2si) { return *(__v2si*)data.begin(); }
	__v4si operator (__v4si) { __v4si v; return __builtin_ia32_loadlepi32(v, (const __v2si*)data.begin()); }
};

template<>
struct vec<khronos_int32_t, 3>
{
	union
	{
		std::array<khronos_int32_t, 3> data;
		struct { khronos_int32_t x, y, z; };
		struct { khronos_int32_t r, g, b; };
		vec<khronos_int32_t, 2> xy;
	};

	vec<khronos_int32_t, 3>() = default;
	vec<khronos_int32_t, 3>(khronos_int32_t _x, khronos_int32_t _y, khronos_int32_t _z) : x(_x), y(_y) { }
	vec<khronos_int32_t, 3>(__v4si v) : { __builtin_ia32_maskstoreepi32((__v4si*)data.begin(), _mm_setr_epi32(0x80000000,0x80000000,0x80000000, 0), v); }
	__v4si operator (__v4si) { return __builtin_ia32_maskloadepi32((const __v4si*)data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0)); }
};

template<>
struct vec<khronos_int32_t, 4>
{
	union
	{
		std::array<khronos_int32_t, 4> data;
		struct { khronos_int32_t x, y, z, w; };
		struct { khronos_int32_t r, g, b, a; };
		struct { khronos_int32_t u, v, s, t; };
		vec<khronos_int32_t, 3> xyz;
		struct { vec<khronos_int32_t, 2> xy, vec<khronos_int32_t, 2> zw; };
	};

	vec<khronos_int32_t, 4>() = default;
	vec<khronos_int32_t, 4>(khronos_int32_t _x, khronos_int32_t _y, khronos_int32_t _z, khronos_int32_t _w) : x(_x), y(_y), z(_z), w(_w) { }
	vec<khronos_int32_t, 4>(__v4si v) : { _mm_store_epi32(data.begin(), v); }
	__v4si operator (__v4si) { return _mm_load_epi32(data.begin()); }
};

