#pragma once

#include "v2f64.h"

template<>
struct vec<double, 3>
{
	union
	{
		std::array<double, 3> data;
		struct { double x, y, z; };
		struct { double r, g, b; };
		vec<double, 2> xy;
	};

	vec<double, 3>() = default;
	vec<double, 3>(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }
	vec<double, 3>(double scalar) {
#ifdef __AVX__
		_mm256_maskstore_pd(data.begin(), _mm256_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0), _mm256_set1_pd(scalar));
#else
		x = y = z = scalar;
#endif
	}
	vec<double, 3>(__v4df v) { __builtin_ia32_maskstorepd((__v4df*)data.begin(), (__v4si)_mm256_setr_epi32(0x80000000,0x80000000,0x80000000, 0), v); }
	vec<double, 3>(const vec<double, 2>& v) : xy(v) { }
	vec<double, 3>(const vec<double, 3>& v) { __builtin_ia32_maskstorepd((__v4df*)data.begin(), (__v4si)_mm256_setr_epi32(0x80000000,0x80000000,0x80000000, 0), *(__v4df*)v.data.begin()); }
	//inline operator __v4df() const { return __builtin_ia32_maskloadps((const __v4df*)data.begin(), (__v4si)_mm256_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0)); }
	vec<double, 3>& operator=(const vec<double, 3>& copy) {
#ifdef __AVX__
		_mm256_maskstore_pd(data.begin(), _mm256_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000),
				_mm256_maskload_pd(copy.data.begin(), _mm256_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000)));
#else
		data[0] = copy.data[0];
		data[1] = copy.data[1];
		data[2] = copy.data[2];
#endif
		return *this;
	}
	vec<double, 3>& operator=(double scalar) {
#ifdef __AVX__
		_mm256_maskstore_pd(data.begin(), _mm256_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000), _mm256_set1_pd(scalar));
#else
		x = y = z = scalar;
#endif
		return *this;
	}
	vec<double, 3>& operator=(const __v4df& vec4) { 
#ifdef __AVX__
		_mm256_maskstore_pd(data.begin(), _mm256_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000), vec4);
#else
		data[0] = vec4[0];
		data[1] = vec4[1];
		data[2] = vec4[2];
#endif
		return *this;
	}

	constexpr double& operator[](ssize_t i) { return data[i]; }
	constexpr const double& operator[](ssize_t i) const { return data[i]; }

	inline constexpr vec<double, 3>& operator+=(const vec<double, 3>& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; return *this; }
	inline constexpr vec<double, 3>& operator-=(const vec<double, 3>& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; return *this; }
	inline constexpr vec<double, 3>& operator*=(const vec<double, 3>& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; return *this; }
	inline constexpr vec<double, 3>& operator*=(double rhs)       { x*=rhs;   y*=rhs;   z*=rhs  ; return *this; }
	inline constexpr vec<double, 3>& operator/=(const vec<double, 3>& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; return *this; }
	inline constexpr vec<double, 3>& operator/=(double rhs)       { x/=rhs;   y/=rhs;   z/=rhs  ; return *this; }

	inline vec<double, 3> operator-() const { return vec<double, 3>(-x, -y, -z); }
	constexpr vec<double, 3> operator+() const { return *this; }

	inline vec<double, 3> operator+(const vec<double, 3>& lhs, const vec<double, 3>& rhs) { return vec<double, 3>(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z); }
	inline vec<double, 3> operator-(const vec<double, 3>& lhs, const vec<double, 3>& rhs) { return vec<double, 3>(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z); }
	inline vec<double, 3> operator*(const vec<double, 3>& lhs, const vec<double, 3>& rhs) { return vec<double, 3>(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z); }
	inline vec<double, 3> operator*(const vec<double, 3>& lhs, double rhs)       { return vec<double, 3>(lhs.x*rhs,   lhs.y*rhs,   lhs.z*rhs  ); }
	inline vec<double, 3> operator/(const vec<double, 3>& lhs, const vec<double, 3>& rhs) { return vec<double, 3>(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z); }
	inline vec<double, 3> operator/(const vec<double, 3>& lhs, double rhs)       { return vec<double, 3>(lhs.x/rhs,   lhs.y/rhs,   lhs.z/rhs  ); }

	inline constexpr bool operator==(const vec<double, 3>& lhs, const vec<double, 3>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
	inline constexpr bool operator!=(const vec<double, 3>& lhs, const vec<double, 3>& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z; }

	inline vec<double,3>& floor()	{ x = floor(x); y = floor(y); z = floor(z); return *this; }
	inline vec<double,3>& ceil()	{ x = ceil(x); y = ceil(y); z = ceil(z); return *this; }
};

inline vec<double, 3> floor(const vec<double, 3>& v)	{ return vec<double, 3>(floor(v.x), floor(v.y), floor(v.z)); }
inline vec<double, 3> ceil(const vec<double, 3>& v)	{ return vec<double, 3>(ceil(v.x), ceil(v.y), ceil(v.z)); }

