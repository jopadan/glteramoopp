#pragma once

#include "v2f32.h"

template<>
struct vec<float, 3>
{
	union
	{
		std::array<float, 3> data;
		struct { float x, y, z; };
		struct { float r, g, b; };
		vec<float, 2> xy;
	};

	vec<float, 3>() = default;
	vec<float, 3>(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
	vec<float, 3>(float scalar) {
#ifdef __AVX__
		_mm_maskstore_ps(data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0), _mm_set1_ps(scalar));
#else
		x = y = z = scalar;
#endif
	}
	vec<float, 3>(__v4sf v) { __builtin_ia32_maskstoreps((__v4sf*)data.begin(), (__v4si)_mm_setr_epi32(0x80000000,0x80000000,0x80000000, 0), v); }
	vec<float, 3>(const vec<float, 2>& v) : xy(v) { }
	vec<float, 3>(const vec<float, 3>& v) { __builtin_ia32_maskstoreps((__v4sf*)data.begin(), (__v4si)_mm_setr_epi32(0x80000000,0x80000000,0x80000000, 0), *(__v4sf*)v.data.begin()); }
	//inline operator __v4sf() const { return __builtin_ia32_maskloadps((const __v4sf*)data.begin(), (__v4si)_mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0)); }
	vec<float, 3>& operator=(const vec<float, 3>& copy) {
#ifdef __AVX__
		_mm_maskstore_ps(data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000),
				_mm_maskload_ps(copy.data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000)));
#else
		data[0] = copy.data[0];
		data[1] = copy.data[1];
		data[2] = copy.data[2];
#endif
		return *this;
	}
	vec<float, 3>& operator=(float scalar) {
#ifdef __AVX__
		_mm_maskstore_ps(data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000), _mm_set1_ps(scalar));
#else
		x = y = z = scalar;
#endif
		return *this;
	}
	vec<float, 3>& operator=(const __v4sf& vec4) { 
#ifdef __AVX__
		_mm_maskstore_ps(data.begin(), _mm_setr_epi32(0x80000000, 0x80000000, 0x80000000, 0x00000000), vec4);
#else
		data[0] = vec4[0];
		data[1] = vec4[1];
		data[2] = vec4[2];
#endif
		return *this;
	}

	constexpr float& operator[](ssize_t i) { return data[i]; }
	constexpr const float& operator[](ssize_t i) const { return data[i]; }

	inline constexpr vec<float, 3>& operator+=(const vec<float, 3>& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; return *this; }
	inline constexpr vec<float, 3>& operator-=(const vec<float, 3>& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; return *this; }
	inline constexpr vec<float, 3>& operator*=(const vec<float, 3>& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; return *this; }
	inline constexpr vec<float, 3>& operator*=(float rhs)       { x*=rhs;   y*=rhs;   z*=rhs  ; return *this; }
	inline constexpr vec<float, 3>& operator/=(const vec<float, 3>& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; return *this; }
	inline constexpr vec<float, 3>& operator/=(float rhs)       { x/=rhs;   y/=rhs;   z/=rhs  ; return *this; }

	inline vec<float, 3> operator-() const { return vec<float, 3>(-x, -y, -z); }
	constexpr vec<float, 3> operator+() const { return *this; }

	inline vec<float, 3> operator+(const vec<float, 3>& lhs, const vec<float, 3>& rhs) { return vec<float, 3>(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z); }
	inline vec<float, 3> operator-(const vec<float, 3>& lhs, const vec<float, 3>& rhs) { return vec<float, 3>(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z); }
	inline vec<float, 3> operator*(const vec<float, 3>& lhs, const vec<float, 3>& rhs) { return vec<float, 3>(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z); }
	inline vec<float, 3> operator*(const vec<float, 3>& lhs, float rhs)       { return vec<float, 3>(lhs.x*rhs,   lhs.y*rhs,   lhs.z*rhs  ); }
	inline vec<float, 3> operator/(const vec<float, 3>& lhs, const vec<float, 3>& rhs) { return vec<float, 3>(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z); }
	inline vec<float, 3> operator/(const vec<float, 3>& lhs, float rhs)       { return vec<float, 3>(lhs.x/rhs,   lhs.y/rhs,   lhs.z/rhs  ); }

	inline constexpr bool operator==(const vec<float, 3>& lhs, const vec<float, 3>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
	inline constexpr bool operator!=(const vec<float, 3>& lhs, const vec<float, 3>& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z; }

	inline vec<float, 3> floor(const vec<float, 3>& v)	{ return vec<float, 3>(floorf(v.x), floorf(v.y), floorf(v.z)); }
	inline vec<float, 3> ceil(const vec<float, 3>& v)	{ return vec<float, 3>(ceilf(v.x), ceilf(v.y), ceilf(v.z)); }

};

inline vec<float, 3> cross(const vec<float, 3>& lhs, const vec<float, 3>& rhs) {
#ifdef __AVX__
	std::array<vec<float, 3>, 2> dst = { _mm_permute_ps(*(__v4sf*)lhs.data.begin(), 0b11001001), _mm_permute_ps(*(__v4sf*)rhs.data.begin(), 0b11001001) };
	return _mm_permute_ps(*(__v4sf*)(lhs * dst[1] - rhs * dst[0]).data.begin(), 0b11001001);
#else
	vec<float, 3> dst;
	dst.data[2] = lhs.data[0] * rhs.data[1] - rhs.data[0] * lhs.data[1];
	dst.data[0] = lhs.data[1] * rhs.data[2] - rhs.data[1] * lhs.data[2];
	dst.data[1] = lhs.data[2] * rhs.data[0] - rhs.data[2] * lhs.data[0];
	dst.data[3] = 0.0f;

	return dst;
#endif
}

inline float dot(const vec<float, 3>& lhs, const vec<float, 3>& rhs) {
#ifdef __SSE4_1__
	return _mm_dp_ps(*(__v4sf*)lhs.data.begin(), *(__v4sf*)rhs.data.begin(), 0b1111)[0];
#else
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
#endif
}

}
