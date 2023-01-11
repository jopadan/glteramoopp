#pragma once
#include "vector.h"

template<>
struct vec<GLdouble, 2>
{
	union
	{
		std::array<GLdoyble, 2> data;
		struct { GLdouble x, GLdouble y; };
		struct { GLdouble u, GLdouble v; };
		struct { GLdouble s, GLdouble t; };
		struct { GLdouble w, GLdouble h; };
	};

	vec<GLdouble, 2>() = default;
	vec<GLdouble, 2>(GLdouble _x, GLdouble _y) : x(_x), y(_y) { }
	vec<GLdouble, 2>(__v2df v) : { __v4df tmp; _mm_store_pd(data.begin(), v); }
	__v2df operator (__v2df) { return _mm_load_pd(data.begin()); }
};

template<>
struct vec<GLdouble, 3>
{
	union
	{
		std::array<GLdouble, 3> data;
		struct { GLdouble x, y, z; };
		struct { GLdouble r, g, b; };
		vec<GLdouble, 2> xy;
	};

	vec<GLdouble, 3>() = default;
	vec<GLdouble, 3>(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) { }
	vec<GLdouble, 3>(__v4df v) : { __builtin_ia32_maskstorepd256((__v4df*)data.begin(), _mm_setr_epi32(0x80000000,0x80000000,0x80000000, 0), v); }
	__v4df operator (__v4df) { return __builtin_ia32_maskloadpd256((const __v4df*)data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0)); }
};

template<>
struct vec<GLdouble, 4>
{
	union
	{
		std::array<GLdouble, 4> data;
		struct { GLdouble x, y, z, w; };
		struct { GLdouble r, g, b, a; };
		struct { GLdouble u, v, s, t; };
		vec<GLdouble, 3> xyz;
		struct { vec<GLdouble, 2> xy, vec<GLdouble, 2> zw; };
	};

	vec<GLdouble, 4>() = default;
	vec<GLdouble, 4>(GLdouble _x, GLdouble _y, GLdouble _z, GLdouble _w) : x(_x), y(_y), z(_z), w(_w) { }
	vec<GLdouble, 4>(__v4df v) : { _mm256_store_pd(data.begin(), v); }
	__v4df operator (__v4df) { return _mm256_load_pd(data.begin()); }
};
