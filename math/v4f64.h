#pragma once
#include "types.h"
#include "v2f64.h"
#include "v3f64.h"

template<>
struct vec<double, 4>
{
	union
	{
		std::array<double, 4> data;
		struct { double x, y, z, w; };
		struct { double r, g, b, a; };
		struct { double u, v, s, t; };
		vec<double, 3> xyz;
	};

	vec<double, 4>() = default;
	constexpr vec<double, 4>(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) { }
	vec<double, 4>(__v4df v) { _mm256_store_pd(data.begin(), v); }
	vec<double, 4>(const vec<double, 2>& v) {
#ifdef __SSE__
		__builtin_ia32_storelpd((__v2df*)data.begin(), *(__v4df*)v.data.begin());
#else
		data[0] = v.data[0];
		data[1] = v.data[1];
#endif
	}
	vec<double, 4>(const vec<double, 3>& v) { xyz = v; }
	vec<double, 4>(const vec<double, 4>& v) {
#ifdef __SSE__
		*(__v4df*)data.begin() = *(__v4df*)v.data.begin();
#else
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = v.data[3];
#endif
	}
#ifdef __SSE__
	inline operator __v4df() { return *(__v4df*)data.begin(); }
	vec<double, 4>& operator=(const __v4df& v) { _mm256_store_pd(data.begin(), v); return *this; }
#endif
	inline operator const std::array<double, 4>&() const { return data; }
	inline operator std::array<double, 4>&() { return data; }
	inline operator std::array<double, 4>() { return data; }
	inline operator const double*() const { return data.begin(); }
	vec<double, 4>& operator=(const vec<double, 4>& copy) { *(__v4df*)data.begin() = *(__v4df*)copy.data.begin(); return *this; }
	vec<double, 4>& operator=(double scalar) { x = scalar; y = scalar; z = scalar; w = scalar; return *this; }
	double& operator[](ssize_t i) { return data[i]; }
	constexpr const double& operator[](ssize_t i) const { return data[i]; }

	inline constexpr vec<double, 4>& operator+=(const vec<double, 4>& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; w+=rhs.w; return *this; }
	inline constexpr vec<double, 4>& operator-=(const vec<double, 4>& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; w+=rhs.w; return *this; }
	inline constexpr vec<double, 4>& operator*=(const vec<double, 4>& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; w*=rhs.w; return *this; }
	inline constexpr vec<double, 4>& operator*=(double rhs)                { x*=rhs;   y*=rhs;   z*=rhs;   w*=rhs  ; return *this; }
	inline constexpr vec<double, 4>& operator/=(const vec<double, 4>& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; w/=rhs.w; return *this; }
	inline constexpr vec<double, 4>& operator/=(double rhs)                { x/=rhs;   y/=rhs;   z/=rhs;   w/=rhs  ; return *this; }

	inline constexpr vec<double, 4> operator-() const                     { return vec<double, 4>(-x, -y, -z, -w); }
	inline vec<double, 4> operator+() const                               { return *this; }
	inline vec<double, 4>& operator++() {
#ifdef __SSE__
		*(__v4df*)data.begin() = _mm256_add_pd(*(__v4df*)data.begin(), _mm256_set1_pd(1.0f)); return *this;
#else
		x+=1.0f; y+=1.0f; z+=1.0f; w+=1.0f; return *this;
#endif
	}
	inline vec<double, 4> operator++(int) {
		vec<double, 4> tmp = *this;
#ifdef __SSE__
		*(__v4df*)data.begin() = _mm256_add_pd(*(__v4df*)data.begin(), _mm256_set1_pd(1.0f));
#else
		x+=1.0f; y+=1.0f; z+=1.0f; w+=1.0f;
#endif
		return tmp;
	}
	inline vec<double, 4>& operator--() {
#ifdef __SSE__
		*(__v4df*)data.begin() = _mm256_sub_pd(*(__v4df*)data.begin(), _mm256_set1_pd(1.0f)); return *this;
#else
		x-=1.0f; y-=1.0f; z-=1.0f; w-=1.0f; return *this;
#endif
	}
	inline vec<double, 4> operator--(int) {
		vec<double, 4> tmp = *this;
#ifdef __SSE__
		*(__v4df*)data.begin() = _mm256_add_pd(*(__v4df*)data.begin(), _mm256_set1_pd(1.0f));
#else
		x+=1.0f; y+=1.0f; z+=1.0f; w+=1.0f;
#endif
		return tmp;
	}
};

inline vec<double, 4> operator+(const vec<double, 4>& lhs, const vec<double, 4>& rhs) { 
#ifdef __SSE__
	return vec<double, 4>(_mm256_add_pd(_mm256_load_pd(lhs.data.begin()), _mm256_load_pd(rhs.data.begin())));
#else
	return vec<double, 4>(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, lhs.w+rhs.w);
#endif
}

inline vec<double, 4> operator-(const vec<double, 4>& lhs, const vec<double, 4>& rhs) { 
#ifdef __SSE__
	return vec<double, 4>(_mm256_sub_pd(_mm256_load_pd(lhs.data.begin()), _mm256_load_pd(rhs.data.begin())));
#else
	return vec<double, 4>(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z, lhs.w-rhs.w);
#endif
}

inline vec<double, 4> operator*(const vec<double, 4>& lhs, const vec<double, 4>& rhs) { 
#ifdef __SSE__
	return vec<double, 4>(_mm256_mul_pd(_mm256_load_pd(lhs.data.begin()), _mm256_load_pd(rhs.data.begin())));
#else
	return vec<double, 4>(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z, lhs.w*rhs.w);
#endif
}

inline vec<double, 4> operator*(const vec<double, 4>& lhs, double rhs) { 
#ifdef __SSE__
	return vec<double, 4>(_mm256_mul_pd(_mm256_load_pd(lhs.data.begin()), _mm256_set1_pd(rhs)));
#else
	return vec<double, 4>(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs, lhs.w*rhs);
#endif
}

inline vec<double, 4> operator/(const vec<double, 4>& lhs, const vec<double, 4>& rhs) { 
#ifdef __SSE__
	return vec<double, 4>(_mm256_div_pd(_mm256_load_pd(lhs.data.begin()), _mm256_load_pd(rhs.data.begin())));
#else
	return vec<double, 4>(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z, lhs.w/rhs.w);
#endif
}

inline vec<double, 4> operator/(const vec<double, 4>& lhs, double rhs) {
#ifdef __SSE__
	return vec<double, 4>(_mm256_div_pd(_mm256_load_pd(lhs.data.begin()), _mm256_set1_pd(rhs)));
#else
	return vec<double, 4>(lhs.x/rhs, lhs.y/rhs, lhs.z/rhs, lhs.w/rhs);
#endif
}

inline constexpr bool operator==(const vec<double, 4>& lhs, const vec<double, 4>& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline constexpr bool operator!=(const vec<double, 4>& lhs, const vec<double, 4>& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

inline vec<double, 4> floor(const vec<double, 4>& v)	{ return vec<double, 4>(floor(v.x), floor(v.y), floor(v.z), floor(v.w)); }
inline vec<double, 4> ceil(const vec<double, 4>& v)	{ return vec<double, 4>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.z)); }

inline vec<double, 4> cross3(const vec<double, 4>& lhs, const vec<double, 4>& rhs) {
#ifdef __AVX__
	std::array<vec<double, 4>, 2> dst = { _mm256_permute_pd(*(__v4df*)lhs.data.begin(), 0b11001001), _mm256_permute_pd(*(__v4df*)rhs.data.begin(), 0b11001001) };
	return _mm256_permute_pd(*(__v4df*)(lhs * dst[1] - rhs * dst[0]).data.begin(), 0b11001001);
#else
	vec<double, 4> dst;
	dst.data[2] = lhs.data[0] * rhs.data[1] - rhs.data[0] * lhs.data[1];
	dst.data[0] = lhs.data[1] * rhs.data[2] - rhs.data[1] * lhs.data[2];
	dst.data[1] = lhs.data[2] * rhs.data[0] - rhs.data[2] * lhs.data[0];
	dst.data[3] = 0.0f;

	return _mm256_dp_pd(*(__v4df*)lhs.data.begin(), *(__v4df*)rhs.data.begin(), 0b1111)[0];
#else
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
#endif
}
};
