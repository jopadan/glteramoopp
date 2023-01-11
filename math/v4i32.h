#pragma once
#include "types.h"
#include "v2f32.h"
#include "v3f32.h"

struct INTVECTOR4 {
	union {
		std::array<INT, 4> data;
		struct { INT x, y, z, w; };
		struct { INT r, g, b, a; };
		struct { INT u, v, s, t; };
		INTVECTOR3 xyz;
		std::array<INTVECTOR2, 2> data2;
	};

	INTVECTOR4() = default;
	INTVECTOR4(const __v4hi& vec4) { _mm_store_ps(&data[0], vec4);  }
	INTVECTOR4(const INTVECTOR3& vec3) { xyz = vec3; w = 0; }
	INTVECTOR4(const INTVECTOR2& vec2) { data2 = { vec2, INTVECTOR2(0, 0) }; }
	INTVECTOR4(const INTVECTOR2& a, const INTVECTOR2& b) { data2 = { a, b }; }
	constexpr INTVECTOR4(INT x, INT y, INT z, INT w) : x(x), y(y), z(z), w(w) { }
	constexpr INTVECTOR4(INT scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }
	inline operator __v4hi() const                    { return *(__v4hi*)&(this->data[0]); }
	inline operator const INT*() const              { return &(this->data[0]); }
	INTVECTOR4& operator=(const INTVECTOR4& copy) { (*this) = (__v4hi)copy; return *this; }
	INTVECTOR4& operator=(INT scalar)             { x = scalar; y = scalar; z = scalar; w = scalar; return *this; }
	INTVECTOR4& operator=(const __v4hi& vec4)       { _mm_store_ps(&data[0], vec4); return *this; }
	constexpr INT& operator[](size_t i)             { return data[i]; }
	constexpr const INT& operator[](size_t i) const { return data[i]; }

	inline constexpr INTVECTOR4& operator+=(const INTVECTOR4& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; w+=rhs.w; return *this; }
	inline constexpr INTVECTOR4& operator-=(const INTVECTOR4& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; w+=rhs.w; return *this; }
	inline constexpr INTVECTOR4& operator*=(const INTVECTOR4& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; w*=rhs.w; return *this; }
	inline constexpr INTVECTOR4& operator*=(INT rhs)       { x*=rhs;   y*=rhs;   z*=rhs;   w*=rhs  ; return *this; }
	inline constexpr INTVECTOR4& operator/=(const INTVECTOR4& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; w/=rhs.w; return *this; }
	inline constexpr INTVECTOR4& operator/=(INT rhs)       { x/=rhs;   y/=rhs;   z/=rhs;   w/=rhs  ; return *this; }
	
	inline constexpr INTVECTOR4 operator-() const { return INTVECTOR4(-x, -y, -z, -w); }
	inline constexpr INTVECTOR4 operator+() const { return *this; }
};

inline constexpr INTVECTOR4 operator+(const INTVECTOR4& lhs, const INTVECTOR4& rhs) { return INTVECTOR4(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, lhs.w+rhs.w); }
inline constexpr INTVECTOR4 operator-(const INTVECTOR4& lhs, const INTVECTOR4& rhs) { return INTVECTOR4(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z, lhs.w-rhs.w); }
inline constexpr INTVECTOR4 operator*(const INTVECTOR4& lhs, const INTVECTOR4& rhs) { return INTVECTOR4(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z, lhs.w*rhs.w); }
inline constexpr INTVECTOR4 operator*(const INTVECTOR4& lhs, INT rhs)               { return INTVECTOR4(lhs.x*rhs,   lhs.y*rhs,   lhs.z*rhs,   lhs.w*rhs  ); }
inline constexpr INTVECTOR4 operator/(const INTVECTOR4& lhs, const INTVECTOR4& rhs) { return INTVECTOR4(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z, lhs.w/rhs.w); }
inline constexpr INTVECTOR4 operator/(const INTVECTOR4& lhs, INT rhs)               { return INTVECTOR4(lhs.x/rhs,   lhs.y/rhs,   lhs.z/rhs,   lhs.w/rhs  ); }

inline constexpr bool operator==(const INTVECTOR4& lhs, const INTVECTOR4& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline constexpr bool operator!=(const INTVECTOR4& lhs, const INTVECTOR4& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

inline INTVECTOR4 floor(const INTVECTOR4& v) { return INTVECTOR4(floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w)); }
inline INTVECTOR4 ceil(const INTVECTOR4& v)	 { return INTVECTOR4(ceilf(v.x), ceilf(v.y), ceilf(v.z), ceilf(v.z)); }

inline INTVECTOR4 cross3(const INTVECTOR4& lhs, const INTVECTOR4& rhs) {
	INTVECTOR4 dst;
	dst[2] = lhs[0] * rhs[1] - rhs[0] * lhs[1];
	dst[0] = lhs[1] * rhs[2] - rhs[1] * lhs[2];
	dst[1] = lhs[2] * rhs[0] - rhs[2] * lhs[0];
	dst[3] = 0;

	return dst;
}

inline INT dot(const INTVECTOR4& lhs, const INTVECTOR4& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
