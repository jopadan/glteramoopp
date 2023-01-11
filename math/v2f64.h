#pragma once

#include "types.h"

template<>
struct vec<double, 2>
{
	union
	{
		std::array<double, 2> data;
		struct { double x, y; };
		struct { double u, v; };
		struct { double s, t; };
		struct { double w, h; };
	};

	vec<double, 2>() = default;
	vec<double, 2>(double _x, double _y) : x(_x), y(_y) { }
	constexpr vec<double, 2>(double scalar) : x(scalar), y(scalar) { }
#ifdef __SSE__
	vec<double, 2>(__v2df v) { _mm_store_pd((__v2df*)data.begin(), v); } 
	vec<double, 2>(__v4sf v) { __builtin_ia32_storelpd((__v2df*)data.begin(), v); }
#endif
	vec<double, 2>(const vec<double, 2>& v) { __v4sf tmp; __builtin_ia32_storelpd((__v2df*)data.begin(), __builtin_ia32_loadlpd(tmp, (__v2df*)v.data.begin())); }
	inline operator __v2df() const { return *(__v2df*)data.begin(); }
	inline operator const double*() const { return data.begin(); }
	vec<double, 2>& operator=(const vec<double, 2>& copy) {  data[0] = copy.data[0]; data[1] = copy.data[1]; return *this; }
	vec<double, 2>& operator=(double scalar) { x = y = scalar; return *this; }
	constexpr double&	operator[](ssize_t i) { return data[i]; }
	constexpr const double&	operator[](ssize_t i) const { return data[i]; }

	constexpr vec<double, 2>& operator+=(const vec<double, 2>& rhs) { x+=rhs.x; y+=rhs.y; return *this; }
	constexpr vec<double, 2>& operator-=(const vec<double, 2>& rhs) { x-=rhs.x; y-=rhs.y; return *this; }
	constexpr vec<double, 2>& operator*=(const vec<double, 2>& rhs) { x*=rhs.x; y*=rhs.y; return *this; }
	constexpr vec<double, 2>& operator/=(const vec<double, 2>& rhs) { x/=rhs.x; y/=rhs.y; return *this; }

	constexpr vec<double, 2> operator-() const { return vec<double, 2>(-x, -y); }
	constexpr vec<double, 2> operator+() const { return *this; }
	constexpr vec<double, 2> operator+(const vec<double, 2>& lhs, const vec<double, 2>& rhs) { return vec<double, 2>(lhs.x+rhs.x, lhs.y+rhs.y); }
	constexpr vec<double, 2> operator-(const vec<double, 2>& lhs, const vec<double, 2>& rhs) { return vec<double, 2>(lhs.x-rhs.x, lhs.y-rhs.y); }
	constexpr vec<double, 2> operator*(const vec<double, 2>& lhs, const vec<double, 2>& rhs) { return vec<double, 2>(lhs.x*rhs.x, lhs.y*rhs.y); }
	constexpr vec<double, 2> operator/(const vec<double, 2>& lhs, const vec<double, 2>& rhs) { return vec<double, 2>(lhs.x/rhs.x, lhs.y/rhs.y); }

	constexpr bool operator==(const vec<double, 2>& lhs, const vec<double, 2>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	constexpr bool operator!=(const vec<double, 2>& lhs, const vec<double, 2>& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }
};


vec<double, 2> floor(const vec<double, 2>& v)	{ return vec<double, 2>(floorf(v.x), floorf(v.y)); }
vec<double, 2> ceil(const vec<double, 2>& v)	{ return vec<double, 2>(ceilf(v.x), ceilf(v.y)); }

inline vec<double, 2> cross(const vec<double, 2>& lhs, const vec<double, 2>& rhs) {
#ifdef __AVX__
	union {
	__v2df t[2];
	__v4df t4;
	};
	tmp[0] = _mm_load_pd(lhs.data.begin());
	tmp[1] = _mm_load_pd(rhs.data.begin());
	return vec<double, 2>(_mm256_permute_pd(t4, 0b10110001), t);
	return vec<double, 2> res(dst[0] * _mm256_load_pd(&tmp[0]));
#else
	vec<double, 2> dst;
	dst[0] = lhs.data[0] * rhs.data[1] - rhs.data[1] * lhs.data[0];
	dst[1] = lhs.data[1] * rhs.data[0] - rhs.data[0] * lhs.data[1];

	return dst;
#endif
}

inline double dot(const vec<double, 2>& lhs, const vec<double, 2>& rhs) {
#ifdef __SSE4_1__
	return _mm_dp_pd(_mm_load_pd(lhs.data.begin()), _mm_load_pd(rhs.data.begin()), 0xFF)[0];
#else
	return lhs.x * rhs.x + lhs.y * rhs.y;
#endif
}
