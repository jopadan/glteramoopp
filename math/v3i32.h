#pragma once

#include "v2f32.h"

struct INTVECTOR3 {
	union {
		std::array<INT, 3> data;
		struct { INT x, y, z; };
		struct { INT r, g, b; };
		INTVECTOR2 xy;
	};

	/* constructors */
	INTVECTOR3() = default;
	constexpr INTVECTOR3(INT _x_, INT _y_, INT _z_) : x(_x_), y(_y_), z(_z_) { }
	constexpr INTVECTOR3(INT scalar) : x(scalar), y(scalar), z(scalar) { }
	constexpr INTVECTOR3(const __v4hi& vec4) : x(vec4[0]), y(vec4[1]), z(vec4[2]) { }

	/* arithmetic operators */
	inline constexpr INTVECTOR3 operator+(const INTVECTOR3& lhs, const INTVECTOR3& rhs) { return INTVECTOR3(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z); }
	inline constexpr INTVECTOR3 operator-(const INTVECTOR3& lhs, const INTVECTOR3& rhs) { return INTVECTOR3(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z); }
	inline constexpr INTVECTOR3 operator*(const INTVECTOR3& lhs, const INTVECTOR3& rhs) { return INTVECTOR3(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z); }
	inline constexpr INTVECTOR3 operator*(const INTVECTOR3& lhs, INT rhs)       { return INTVECTOR3(lhs.x*rhs,   lhs.y*rhs,   lhs.z*rhs  ); }
	inline constexpr INTVECTOR3 operator/(const INTVECTOR3& lhs, const INTVECTOR3& rhs) { return INTVECTOR3(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z); }
	inline constexpr INTVECTOR3 operator/(const INTVECTOR3& lhs, INT rhs)       { return INTVECTOR3(lhs.x/rhs,   lhs.y/rhs,   lhs.z/rhs  ); }

	/* assignment operators */
	INTVECTOR3& operator=(const INTVECTOR3& copy) {
		data[0] = copy.data[0];
		data[1] = copy.data[1];
		data[2] = copy.data[2];
		return *this;
	}
	INTVECTOR3& operator=(INT scalar)  {
		x = y = z = scalar;
		return *this;
	}
	INTVECTOR3& operator=(const __v4hi& vec4) { 
		data[0] = vec4[0];
		data[1] = vec4[1];
		data[2] = vec4[2];
		return *this;
	}
	inline constexpr INTVECTOR3& operator+=(const INTVECTOR3& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; return *this; }
	inline constexpr INTVECTOR3& operator-=(const INTVECTOR3& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; return *this; }
	inline constexpr INTVECTOR3& operator*=(const INTVECTOR3& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; return *this; }
	inline constexpr INTVECTOR3& operator*=(INT rhs)       { x*=rhs;   y*=rhs;   z*=rhs  ; return *this; }
	inline constexpr INTVECTOR3& operator/=(const INTVECTOR3& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; return *this; }
	inline constexpr INTVECTOR3& operator/=(INT rhs)       { x/=rhs;   y/=rhs;   z/=rhs  ; return *this; }

	/* array index operators */
	constexpr INT& operator[](size_t i) { return data[i]; }
	constexpr const INT& operator[](size_t i) const { return data[i]; }

	/* sign operators */
	inline INTVECTOR3 operator-() const { return INTVECTOR3(-x, -y, -z); }
	constexpr INTVECTOR3 operator+() const { return *this; }

	/* compare operators */
	inline constexpr bool operator==(const INTVECTOR3& lhs, const INTVECTOR3& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
	inline constexpr bool operator!=(const INTVECTOR3& lhs, const INTVECTOR3& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z; }

};

inline INTVECTOR3 floor(const INTVECTOR3& v) { return INTVECTOR3(floorf(v.x), floorf(v.y), floorf(v.z)); }
inline INTVECTOR3 ceil(const INTVECTOR3& v)	 { return INTVECTOR3(ceilf(v.x), ceilf(v.y), ceilf(v.z)); }

/* vector operations */
inline INTVECTOR3 cross(const INTVECTOR3& lhs, const INTVECTOR3& rhs) {
	INTVECTOR3 tmp[4] = { INTVECTOR3(lhs[1], lhs[2], lhs[0]), INTVECTOR3(rhs[1], rhs[2], rhs[0]) };

	tmp[2] = lhs * tmp[1] - rhs * tmp[0];

	tmp[3][2] = tmp[2][0];
	tmp[3][0] = tmp[2][1];
	tmp[3][1] = tmp[2][2];

	return tmp[3];
}
inline INT dot(const INTVECTOR3& lhs, const INTVECTOR3& rhs) { return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2]; }
inline INT norm(const INTVECTOR3& a) { return dot(a,a); }
inline INTVECTOR3 normalize(const INTVECTOR3& a) { return INTVECTOR3(a / norm(a)); }


