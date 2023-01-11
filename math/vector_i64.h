#pragma once
#include "vector.h"

template<>
struct vec<int64_t, 2>
{
	union
	{
		std::array<int64_t, 2> data;
		struct { int64_t x, int64_t y; };
		struct { int64_t u, int64_t v; };
		struct { int64_t s, int64_t t; };
		struct { int64_t w, int64_t h; };
	};

	vec<int64_t, 2>() = default;
	vec<int64_t, 2>(int64_t _x, int64_t _y) : x(_x), y(_y) { }
	vec<int64_t, 2>(__v2si v) : { __v4si tmp; __builtin_ia32_storelepi32((__v2si*)data.begin(), __builtin_ia32_loadlepi32(tmp, &v); }
	vec<int64_t, 2>(__v4si v) : { __builtin_ia32_storelepi32((__v2si*)data.begin(), v); }
	__v2si operator (__v2si) { return *(__v2si*)data.begin(); }
	__v4si operator (__v4si) { __v4si v; return __builtin_ia32_loadlepi32(v, (const __v2si*)data.begin()); }
};

template<>
struct vec<int64_t, 3>
{
	union
	{
		std::array<int64_t, 3> data;
		struct { int64_t x, y, z; };
		struct { int64_t r, g, b; };
		vec<int64_t, 2> xy;
	};

	vec<int64_t, 3>() = default;
	vec<int64_t, 3>(int64_t _x, int64_t _y, int64_t _z) : x(_x), y(_y) { }
	vec<int64_t, 3>(__v4si v) : { __builtin_ia32_maskstoreepi64((__v4si*)data.begin(), _mm_setr_epi32(0x80000000,0x80000000,0x80000000, 0), v); }
	__v4si operator (__v4si) { return __builtin_ia32_maskloadepi64((const __v4si*)data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0)); }
};

template<>
struct vec<int64_t, 4>
{
	union
	{
		std::array<int64_t, 4> data;
		struct { int64_t x, y, z, w; };
		struct { int64_t r, g, b, a; };
		struct { int64_t u, v, s, t; };
		vec<int64_t, 3> xyz;
		struct { vec<int64_t, 2> xy, vec<int64_t, 2> zw; };
	};

	vec<int64_t, 4>() = default;
	vec<int64_t, 4>(int64_t _x, int64_t _y, int64_t _z, int64_t _w) : x(_x), y(_y), z(_z), w(_w) { }
	vec<int64_t, 4>(__v4si v) : { _mm_store_epi32(data.begin(), v); }
	__v4si operator (__v4si) { return _mm_load_epi32(data.begin()); }
};

