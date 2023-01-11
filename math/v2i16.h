#pragma once

#include "types.h"
#include <experimental/simd>
#include <array>

struct SHORTVECTOR2 {
	union {
		std::array<SHORT, 2> data;
		struct { SHORT x, y; };
		struct { SHORT u, v; };
		struct { SHORT s, t; };
		struct { SHORT w, h; };
	};

	SHORTVECTOR2() = default;
	SHORTVECTOR2(__v2sf vec2) { __v4sf vec4 = __builtin_ia32_loadlps(vec4, &vec2); __builtin_ia32_storelps((__v2sf*)&data[0],vec4); } 
	constexpr SHORTVECTOR2(SHORT x, SHORT y) : x(x), y(y) { }
	constexpr SHORTVECTOR2(SHORT scalar) : x(scalar), y(scalar) { }
	inline operator __v2sf() const { return *(__v2sf*)&(this->data[0]); }
	inline operator const SHORT*() const { return &(this->data[0]); }
	SHORTVECTOR2& operator=(const SHORTVECTOR2& copy) { (*this) = (__v2sf)copy; return *this; }
	SHORTVECTOR2& operator=(SHORT scalar) { x = y = scalar; return *this; }
	SHORTVECTOR2& operator=(const __v2sf& vec2) { __v4sf vec4 = __builtin_ia32_loadlps(vec4, &vec2); __builtin_ia32_storelps((__v2sf*)&data[0], vec4); return *this; }

	constexpr SHORT&	operator[](size_t i) { return data[i]; }
	constexpr const SHORT&	operator[](size_t i) const { return data[i]; }

	constexpr SHORTVECTOR2& operator+=(const SHORTVECTOR2& rhs) { x+=rhs.x; y+=rhs.y; return *this; }
	constexpr SHORTVECTOR2& operator-=(const SHORTVECTOR2& rhs) { x-=rhs.x; y-=rhs.y; return *this; }
	constexpr SHORTVECTOR2& operator*=(const SHORTVECTOR2& rhs) { x*=rhs.x; y*=rhs.y; return *this; }
	constexpr SHORTVECTOR2& operator/=(const SHORTVECTOR2& rhs) { x/=rhs.x; y/=rhs.y; return *this; }

	constexpr SHORTVECTOR2 operator-() const { return SHORTVECTOR2(-x, -y); }
	constexpr SHORTVECTOR2 operator+() const { return *this; }
};

constexpr SHORTVECTOR2 operator+(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) { return SHORTVECTOR2(lhs.x+rhs.x, lhs.y+rhs.y); }
constexpr SHORTVECTOR2 operator-(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) { return SHORTVECTOR2(lhs.x-rhs.x, lhs.y-rhs.y); }
constexpr SHORTVECTOR2 operator*(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) { return SHORTVECTOR2(lhs.x*rhs.x, lhs.y*rhs.y); }
constexpr SHORTVECTOR2 operator/(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) { return SHORTVECTOR2(lhs.x/rhs.x, lhs.y/rhs.y); }

constexpr bool operator==(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
constexpr bool operator!=(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }

SHORTVECTOR2 floor(const SHORTVECTOR2& v)	{ return SHORTVECTOR2(floorf(v.x), floorf(v.y)); }
SHORTVECTOR2 ceil(const SHORTVECTOR2& v)	{ return SHORTVECTOR2(ceilf(v.x), ceilf(v.y)); }

inline SHORTVECTOR2 cross(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) {
#ifdef __AVX__
	__v4sf dst[3];
	dst[0] = __builtin_ia32_loadlps((__v4sf)dst[0], (__v2sf*)&lhs);
	dst[0] = __builtin_ia32_loadhps((__v4sf)dst[0], (__v2sf*)&rhs);
	dst[1] = _mm_permute_ps((__v4sf)dst[0], 0b10110001);
	printf("%f %f %f %f\n", dst[1][0], dst[1][1], dst[1][2], dst[1][3]);
	dst[2] = dst[0] * dst[1];
	SHORTVECTOR2 res;
	__builtin_ia32_storelps((__v2sf*)&res, dst[2]);
	return res;
#else
	SHORTVECTOR2 dst;
	dst[0] = lhs[0] * rhs[1] - rhs[1] * lhs[0];
	dst[1] = lhs[1] * rhs[0] - rhs[0] * lhs[1];

	return dst;
#endif
}

inline SHORT dot(const SHORTVECTOR2& lhs, const SHORTVECTOR2& rhs) {
#ifdef __SSE4_1__
	__v4sf dst[2];
	dst[0] = __builtin_ia32_loadlps(dst[0], (__v2sf*)&lhs);
	dst[1] = __builtin_ia32_loadlps(dst[1], (__v2sf*)&rhs);
	return _mm_dp_ps(dst[0], dst[1], 0b1100)[0];
#else
	return lhs.x * rhs.x + lhs.y * rhs.y;
#endif
}
