#pragma once

#include "types.h"
#include <experimental/simd>
#include <array>

struct INTVECTOR2 {
	union {
		std::array<INT, 2> data;
		struct { INT x, y; };
		struct { INT u, v; };
		struct { INT s, t; };
		struct { INT w, h; };
	};

	INTVECTOR2() = default;
	INTVECTOR2(__v2sf vec2) { __v4sf vec4 = __builtin_ia32_loadlps(vec4, &vec2); __builtin_ia32_storelps((__v2sf*)&data[0],vec4); } 
	constexpr INTVECTOR2(INT x, INT y) : x(x), y(y) { }
	constexpr INTVECTOR2(INT scalar) : x(scalar), y(scalar) { }
	inline operator __v2sf() const { return *(__v2sf*)&(this->data[0]); }
	inline operator const INT*() const { return &(this->data[0]); }
	INTVECTOR2& operator=(const INTVECTOR2& copy) { (*this) = (__v2sf)copy; return *this; }
	INTVECTOR2& operator=(INT scalar) { x = y = scalar; return *this; }
	INTVECTOR2& operator=(const __v2sf& vec2) { __v4sf vec4 = __builtin_ia32_loadlps(vec4, &vec2); __builtin_ia32_storelps((__v2sf*)&data[0], vec4); return *this; }

	constexpr INT&	operator[](size_t i) { return data[i]; }
	constexpr const INT&	operator[](size_t i) const { return data[i]; }

	constexpr INTVECTOR2& operator+=(const INTVECTOR2& rhs) { x+=rhs.x; y+=rhs.y; return *this; }
	constexpr INTVECTOR2& operator-=(const INTVECTOR2& rhs) { x-=rhs.x; y-=rhs.y; return *this; }
	constexpr INTVECTOR2& operator*=(const INTVECTOR2& rhs) { x*=rhs.x; y*=rhs.y; return *this; }
	constexpr INTVECTOR2& operator/=(const INTVECTOR2& rhs) { x/=rhs.x; y/=rhs.y; return *this; }

	constexpr INTVECTOR2 operator-() const { return INTVECTOR2(-x, -y); }
	constexpr INTVECTOR2 operator+() const { return *this; }
};

constexpr INTVECTOR2 operator+(const INTVECTOR2& lhs, const INTVECTOR2& rhs) { return INTVECTOR2(lhs.x+rhs.x, lhs.y+rhs.y); }
constexpr INTVECTOR2 operator-(const INTVECTOR2& lhs, const INTVECTOR2& rhs) { return INTVECTOR2(lhs.x-rhs.x, lhs.y-rhs.y); }
constexpr INTVECTOR2 operator*(const INTVECTOR2& lhs, const INTVECTOR2& rhs) { return INTVECTOR2(lhs.x*rhs.x, lhs.y*rhs.y); }
constexpr INTVECTOR2 operator/(const INTVECTOR2& lhs, const INTVECTOR2& rhs) { return INTVECTOR2(lhs.x/rhs.x, lhs.y/rhs.y); }

constexpr bool operator==(const INTVECTOR2& lhs, const INTVECTOR2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
constexpr bool operator!=(const INTVECTOR2& lhs, const INTVECTOR2& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }

INTVECTOR2 floor(const INTVECTOR2& v)	{ return INTVECTOR2(floorf(v.x), floorf(v.y)); }
INTVECTOR2 ceil(const INTVECTOR2& v)	{ return INTVECTOR2(ceilf(v.x), ceilf(v.y)); }

inline INTVECTOR2 cross(const INTVECTOR2& lhs, const INTVECTOR2& rhs) {
#ifdef __AVX__
	__v4sf dst[3];
	dst[0] = __builtin_ia32_loadlps((__v4sf)dst[0], (__v2sf*)&lhs);
	dst[0] = __builtin_ia32_loadhps((__v4sf)dst[0], (__v2sf*)&rhs);
	dst[1] = _mm_permute_ps((__v4sf)dst[0], 0b10110001);
	printf("%f %f %f %f\n", dst[1][0], dst[1][1], dst[1][2], dst[1][3]);
	dst[2] = dst[0] * dst[1];
	INTVECTOR2 res;
	__builtin_ia32_storelps((__v2sf*)&res, dst[2]);
	return res;
#else
	INTVECTOR2 dst;
	dst[0] = lhs[0] * rhs[1] - rhs[1] * lhs[0];
	dst[1] = lhs[1] * rhs[0] - rhs[0] * lhs[1];

	return dst;
#endif
}

inline INT dot(const INTVECTOR2& lhs, const INTVECTOR2& rhs) {
#ifdef __SSE4_1__
	__v4sf dst[2];
	dst[0] = __builtin_ia32_loadlps(dst[0], (__v2sf*)&lhs);
	dst[1] = __builtin_ia32_loadlps(dst[1], (__v2sf*)&rhs);
	return _mm_dp_ps(dst[0], dst[1], 0b1100)[0];
#else
	return lhs.x * rhs.x + lhs.y * rhs.y;
#endif
}
