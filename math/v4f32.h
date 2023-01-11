#pragma once
#include "types.h"
#include "v2f32.h"
#include "v3f32.h"

template<>
struct vec<float, 4>
{
	union
	{
		std::array<float, 4> data;
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		struct { float u, v, s, t; };
		vec<float, 3> xyz;
	};

	vec<float, 4>() = default;
	constexpr vec<float, 4>(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }
	vec<float, 4>(__v4sf v) { _mm_store_ps(data.begin(), v); }
	vec<float, 4>(const vec<float, 2>& v) {
#ifdef __SSE__
		__builtin_ia32_storelps((__v2sf*)data.begin(), *(__v4sf*)v.data.begin());
#else
		data[0] = v.data[0];
		data[1] = v.data[1];
#endif
	}
	vec<float, 4>(const vec<float, 3>& v) { xyz = v; }
	vec<float, 4>(const vec<float, 4>& v) {
#ifdef __SSE__
		*(__v4sf*)data.begin() = *(__v4sf*)v.data.begin();
#else
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = v.data[3];
#endif
	}
#ifdef __SSE__
	inline operator __v4sf() { return *(__v4sf*)data.begin(); }
#endif
	inline operator const std::array<float, 4>&() const { return data; }
	inline operator std::array<float, 4>&() { return data; }
	inline operator std::array<float, 4>() { return data; }
	inline operator const float*() const { return data.begin(); }
	vec<float, 4>& operator=(const vec<float, 4>& copy) { *(__v4sf*)data.begin() = *(__v4sf*)copy.data.begin(); return *this; }
	vec<float, 4>& operator=(float scalar) { x = scalar; y = scalar; z = scalar; w = scalar; return *this; }
	vec<float, 4>& operator=(const __v4sf& vec4) { _mm_store_ps(&data[0], vec4); return *this; }
	float& operator[](ssize_t i) { return data[i]; }
	constexpr const float& operator[](ssize_t i) const { return data[i]; }

	inline constexpr vec<float, 4>& operator+=(const vec<float, 4>& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; w+=rhs.w; return *this; }
	inline constexpr vec<float, 4>& operator-=(const vec<float, 4>& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; w+=rhs.w; return *this; }
	inline constexpr vec<float, 4>& operator*=(const vec<float, 4>& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; w*=rhs.w; return *this; }
	inline constexpr vec<float, 4>& operator*=(float rhs)                { x*=rhs;   y*=rhs;   z*=rhs;   w*=rhs  ; return *this; }
	inline constexpr vec<float, 4>& operator/=(const vec<float, 4>& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; w/=rhs.w; return *this; }
	inline constexpr vec<float, 4>& operator/=(float rhs)                { x/=rhs;   y/=rhs;   z/=rhs;   w/=rhs  ; return *this; }

	inline constexpr vec<float, 4> operator-() const                     { return vec<float, 4>(-x, -y, -z, -w); }
	inline vec<float, 4> operator+() const                               { return *this; }
	inline vec<float, 4>& operator++() {
#ifdef __SSE__
		*(__v4sf*)data.begin() = _mm_add_ps(*(__v4sf*)data.begin(), _mm_set1_ps(1.0f)); return *this;
#else
		x+=1.0f; y+=1.0f; z+=1.0f; w+=1.0f; return *this;
#endif
	}
	inline vec<float, 4> operator++(int) {
		vec<float, 4> tmp = *this;
#ifdef __SSE__
		*(__v4sf*)data.begin() = _mm_add_ps(*(__v4sf*)data.begin(), _mm_set1_ps(1.0f));
#else
		x+=1.0f; y+=1.0f; z+=1.0f; w+=1.0f;
#endif
		return tmp;
	}
	inline vec<float, 4>& operator--() {
#ifdef __SSE__
		*(__v4sf*)data.begin() = _mm_sub_ps(*(__v4sf*)data.begin(), _mm_set1_ps(1.0f)); return *this;
#else
		x-=1.0f; y-=1.0f; z-=1.0f; w-=1.0f; return *this;
#endif
	}
	inline vec<float, 4> operator--(int) {
		vec<float, 4> tmp = *this;
#ifdef __SSE__
		*(__v4sf*)data.begin() = _mm_add_ps(*(__v4sf*)data.begin(), _mm_set1_ps(1.0f));
#else
		x+=1.0f; y+=1.0f; z+=1.0f; w+=1.0f;
#endif
		return tmp;
	}
};

inline vec<float, 4> operator+(const vec<float, 4>& lhs, const vec<float, 4>& rhs) { 
#ifdef __SSE__
	return vec<float, 4>(_mm_add_ps(_mm_load_ps(lhs.data.begin()), _mm_load_ps(rhs.data.begin())));
#else
	return vec<float, 4>(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, lhs.w+rhs.w);
#endif
}

inline vec<float, 4> operator-(const vec<float, 4>& lhs, const vec<float, 4>& rhs) { 
#ifdef __SSE__
	return vec<float, 4>(_mm_sub_ps(_mm_load_ps(lhs.data.begin()), _mm_load_ps(rhs.data.begin())));
#else
	return vec<float, 4>(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z, lhs.w-rhs.w);
#endif
}

inline vec<float, 4> operator*(const vec<float, 4>& lhs, const vec<float, 4>& rhs) { 
#ifdef __SSE__
	return vec<float, 4>(_mm_mul_ps(_mm_load_ps(lhs.data.begin()), _mm_load_ps(rhs.data.begin())));
#else
	return vec<float, 4>(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z, lhs.w*rhs.w);
#endif
}

inline vec<float, 4> operator*(const vec<float, 4>& lhs, float rhs) { 
#ifdef __SSE__
	return vec<float, 4>(_mm_mul_ps(_mm_load_ps(lhs.data.begin()), _mm_set1_ps(rhs)));
#else
	return vec<float, 4>(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs, lhs.w*rhs);
#endif
}

inline vec<float, 4> operator/(const vec<float, 4>& lhs, const vec<float, 4>& rhs) { 
#ifdef __SSE__
	return vec<float, 4>(_mm_div_ps(_mm_load_ps(lhs.data.begin()), _mm_load_ps(rhs.data.begin())));
#else
	return vec<float, 4>(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z, lhs.w/rhs.w);
#endif
}

inline vec<float, 4> operator/(const vec<float, 4>& lhs, float rhs) {
#ifdef __SSE__
	return vec<float, 4>(_mm_div_ps(_mm_load_ps(lhs.data.begin()), _mm_set1_ps(rhs)));
#else
	return vec<float, 4>(lhs.x/rhs, lhs.y/rhs, lhs.z/rhs, lhs.w/rhs);
#endif
}

inline constexpr bool operator==(const vec<float, 4>& lhs, const vec<float, 4>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline constexpr bool operator!=(const vec<float, 4>& lhs, const vec<float, 4>& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

inline vec<float, 4> floor(const vec<float, 4>& v)	{ return vec<float, 4>(floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w)); }
inline vec<float, 4> ceil(const vec<float, 4>& v)	{ return vec<float, 4>(ceilf(v.x), ceilf(v.y), ceilf(v.z), ceilf(v.z)); }

inline vec<float, 4> cross3(const vec<float, 4>& lhs, const vec<float, 4>& rhs) {
#ifdef __AVX__
	std::array<vec<float, 4>, 2> dst = { _mm_permute_ps(*(__v4sf*)lhs.data.begin(), 0b11001001), _mm_permute_ps(*(__v4sf*)rhs.data.begin(), 0b11001001) };
	return _mm_permute_ps(*(__v4sf*)(lhs * dst[1] - rhs * dst[0]).data.begin(), 0b11001001);
#else
	vec<float, 4> dst;
	dst.data[2] = lhs.data[0] * rhs.data[1] - rhs.data[0] * lhs.data[1];
	dst.data[0] = lhs.data[1] * rhs.data[2] - rhs.data[1] * lhs.data[2];
	dst.data[1] = lhs.data[2] * rhs.data[0] - rhs.data[2] * lhs.data[0];
	dst.data[3] = 0.0f;

	return dst;
#endif
}

inline float dot(const vec<float, 4>& lhs, const vec<float, 4>& rhs) {
#ifdef __SSE4_1__
	return _mm_dp_ps(*(__v4sf*)lhs.data.begin(), *(__v4sf*)rhs.data.begin(), 0b1111)[0];
#else
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
#endif
}
};
