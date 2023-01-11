#pragma once

#include "types.h"

template<>
struct vec<float, 2>
{
	union
	{
		std::array<float, 2> data;
		struct { float x, y; };
		struct { float u, v; };
		struct { float s, t; };
		struct { float w, h; };
	};

	vec<float, 2>() = default;
	vec<float, 2>(float _x, float _y) : x(_x), y(_y) { }
	constexpr vec<float, 2>(float scalar) : x(scalar), y(scalar) { }
#ifdef __SSE__
	vec<float, 2>(__v2sf v) { __v4sf tmp = __builtin_ia32_loadlps(tmp, &v); __builtin_ia32_storelps((__v2sf*)data.begin(),tmp); } 
	vec<float, 2>(__v4sf v) { __builtin_ia32_storelps((__v2sf*)data.begin(), v); }
#endif
	vec<float, 2>(const vec<float, 2>& v) { __v4sf tmp; __builtin_ia32_storelps((__v2sf*)data.begin(), __builtin_ia32_loadlps(tmp, (__v2sf*)v.data.begin())); }
	inline operator __v2sf() const { return *(__v2sf*)data.begin(); }
	inline operator const float*() const { return data.begin(); }
	vec<float, 2>& operator=(const vec<float, 2>& copy) {  data[0] = copy.data[0]; data[1] = copy.data[1]; return *this; }
	vec<float, 2>& operator=(float scalar) { x = y = scalar; return *this; }
	constexpr float&	operator[](ssize_t i) { return data[i]; }
	constexpr const float&	operator[](ssize_t i) const { return data[i]; }

	constexpr vec<float, 2>& operator+=(const vec<float, 2>& rhs) { x+=rhs.x; y+=rhs.y; return *this; }
	constexpr vec<float, 2>& operator-=(const vec<float, 2>& rhs) { x-=rhs.x; y-=rhs.y; return *this; }
	constexpr vec<float, 2>& operator*=(const vec<float, 2>& rhs) { x*=rhs.x; y*=rhs.y; return *this; }
	constexpr vec<float, 2>& operator/=(const vec<float, 2>& rhs) { x/=rhs.x; y/=rhs.y; return *this; }

	constexpr vec<float, 2> operator-() const { return vec<float, 2>(-x, -y); }
	constexpr vec<float, 2> operator+() const { return *this; }
	constexpr vec<float, 2> operator+(const vec<float, 2>& lhs, const vec<float, 2>& rhs) { return vec<float, 2>(lhs.x+rhs.x, lhs.y+rhs.y); }
	constexpr vec<float, 2> operator-(const vec<float, 2>& lhs, const vec<float, 2>& rhs) { return vec<float, 2>(lhs.x-rhs.x, lhs.y-rhs.y); }
	constexpr vec<float, 2> operator*(const vec<float, 2>& lhs, const vec<float, 2>& rhs) { return vec<float, 2>(lhs.x*rhs.x, lhs.y*rhs.y); }
	constexpr vec<float, 2> operator/(const vec<float, 2>& lhs, const vec<float, 2>& rhs) { return vec<float, 2>(lhs.x/rhs.x, lhs.y/rhs.y); }

	constexpr bool operator==(const vec<float, 2>& lhs, const vec<float, 2>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	constexpr bool operator!=(const vec<float, 2>& lhs, const vec<float, 2>& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }
};


vec<float, 2> floor(const vec<float, 2>& v)	{ return vec<float, 2>(floorf(v.x), floorf(v.y)); }
vec<float, 2> ceil(const vec<float, 2>& v)	{ return vec<float, 2>(ceilf(v.x), ceilf(v.y)); }

inline vec<float, 2> cross(const vec<float, 2>& lhs, const vec<float, 2>& rhs) {
#ifdef __AVX__
	__v4sf dst[3];
	dst[0] = __builtin_ia32_loadlps((__v4sf)dst[0], (__v2sf*)&lhs);
	dst[0] = __builtin_ia32_loadhps((__v4sf)dst[0], (__v2sf*)&rhs);
	dst[1] = _mm_permute_ps((__v4sf)dst[0], 0b10110001);
	printf("%f %f %f %f\n", dst[1][0], dst[1][1], dst[1][2], dst[1][3]);
	dst[2] = dst[0] * dst[1];
	vec<float, 2> res;
	__builtin_ia32_storelps((__v2sf*)&res, dst[2]);
	return res;
#else
	vec<float, 2> dst;
	dst[0] = lhs[0] * rhs[1] - rhs[1] * lhs[0];
	dst[1] = lhs[1] * rhs[0] - rhs[0] * lhs[1];

	return dst;
#endif
}

inline float dot(const vec<float, 2>& lhs, const vec<float, 2>& rhs) {
#ifdef __SSE4_1__
	__v4sf dst[2];
	dst[0] = __builtin_ia32_loadlps(dst[0], (__v2sf*)&lhs);
	dst[1] = __builtin_ia32_loadlps(dst[1], (__v2sf*)&rhs);
	return _mm_dp_ps(dst[0], dst[1], 0b1100)[0];
#else
	return lhs.x * rhs.x + lhs.y * rhs.y;
#endif
}
