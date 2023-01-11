#pragma once
#include "types.h"
#include "v2f32.h"
#include "v3f32.h"

struct SHORTVECTOR4 {
	union {
		std::array<SHORT, 4> data;
		struct { SHORT x, y, z, w; };
		struct { SHORT r, g, b, a; };
		struct { SHORT u, v, s, t; };
		VECTOR3 xyz;
		std::array<VECTOR2, 2> data2;
	};

	SHORTVECTOR4() = default;
	SHORTVECTOR4(const __v4hi& vec4) { _mm_store_ps(&data[0], vec4);  }
	SHORTVECTOR4(const VECTOR3& vec3) { xyz = vec3; w = 0; }
	SHORTVECTOR4(const VECTOR2& vec2) { data2 = { vec2, VECTOR2(0, 0) }; }
	SHORTVECTOR4(const VECTOR2& a, const VECTOR2& b) { data2 = { a, b }; }
	constexpr SHORTVECTOR4(SHORT x, SHORT y, SHORT z, SHORT w) : x(x), y(y), z(z), w(w) { }
	constexpr SHORTVECTOR4(SHORT scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }
	inline operator __v4hi() const                    { return *(__v4hi*)&(this->data[0]); }
	inline operator const SHORT*() const              { return &(this->data[0]); }
	SHORTVECTOR4& operator=(const SHORTVECTOR4& copy) { (*this) = (__v4hi)copy; return *this; }
	SHORTVECTOR4& operator=(SHORT scalar)             { x = scalar; y = scalar; z = scalar; w = scalar; return *this; }
	SHORTVECTOR4& operator=(const __v4hi& vec4)       { _mm_store_ps(&data[0], vec4); return *this; }
	constexpr SHORT& operator[](size_t i)             { return data[i]; }
	constexpr const SHORT& operator[](size_t i) const { return data[i]; }

	inline constexpr SHORTVECTOR4& operator+=(const SHORTVECTOR4& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; w+=rhs.w; return *this; }
	inline constexpr SHORTVECTOR4& operator-=(const SHORTVECTOR4& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; w+=rhs.w; return *this; }
	inline constexpr SHORTVECTOR4& operator*=(const SHORTVECTOR4& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; w*=rhs.w; return *this; }
	inline constexpr SHORTVECTOR4& operator*=(SHORT rhs)       { x*=rhs;   y*=rhs;   z*=rhs;   w*=rhs  ; return *this; }
	inline constexpr SHORTVECTOR4& operator/=(const SHORTVECTOR4& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; w/=rhs.w; return *this; }
	inline constexpr SHORTVECTOR4& operator/=(SHORT rhs)       { x/=rhs;   y/=rhs;   z/=rhs;   w/=rhs  ; return *this; }
	
	inline constexpr SHORTVECTOR4 operator-() const { return SHORTVECTOR4(-x, -y, -z, -w); }
	inline constexpr SHORTVECTOR4 operator+() const { return *this; }
};

inline constexpr SHORTVECTOR4 operator+(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) { return SHORTVECTOR4(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, lhs.w+rhs.w); }
inline constexpr SHORTVECTOR4 operator-(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) { return SHORTVECTOR4(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z, lhs.w-rhs.w); }
inline constexpr SHORTVECTOR4 operator*(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) { return SHORTVECTOR4(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z, lhs.w*rhs.w); }
inline constexpr SHORTVECTOR4 operator*(const SHORTVECTOR4& lhs, SHORT rhs)               { return SHORTVECTOR4(lhs.x*rhs,   lhs.y*rhs,   lhs.z*rhs,   lhs.w*rhs  ); }
inline constexpr SHORTVECTOR4 operator/(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) { return SHORTVECTOR4(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z, lhs.w/rhs.w); }
inline constexpr SHORTVECTOR4 operator/(const SHORTVECTOR4& lhs, SHORT rhs)               { return SHORTVECTOR4(lhs.x/rhs,   lhs.y/rhs,   lhs.z/rhs,   lhs.w/rhs  ); }

inline constexpr bool operator==(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline constexpr bool operator!=(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

inline SHORTVECTOR4 floor(const SHORTVECTOR4& v) { return SHORTVECTOR4(floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w)); }
inline SHORTVECTOR4 ceil(const SHORTVECTOR4& v)	 { return SHORTVECTOR4(ceilf(v.x), ceilf(v.y), ceilf(v.z), ceilf(v.z)); }

inline SHORTVECTOR4 cross3(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) {
	SHORTVECTOR4 dst;
	dst[2] = lhs[0] * rhs[1] - rhs[0] * lhs[1];
	dst[0] = lhs[1] * rhs[2] - rhs[1] * lhs[2];
	dst[1] = lhs[2] * rhs[0] - rhs[2] * lhs[0];
	dst[3] = 0;

	return dst;
}

inline SHORT dot(const SHORTVECTOR4& lhs, const SHORTVECTOR4& rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
