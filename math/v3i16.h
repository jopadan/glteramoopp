#pragma once

#include "v2f32.h"

struct SHORTVECTOR3 {
	union {
		std::array<SHORT, 3> data;
		struct { SHORT x, y, z; };
		struct { SHORT r, g, b; };
		SHORTVECTOR2 xy;
	};

	/* constructors */
	SHORTVECTOR3() = default;
	constexpr SHORTVECTOR3(SHORT _x_, SHORT _y_, SHORT _z_) : x(_x_), y(_y_), z(_z_) { }
	constexpr SHORTVECTOR3(SHORT scalar) : x(scalar), y(scalar), z(scalar) { }
	constexpr SHORTVECTOR3(const __v4hi& vec4) : x(vec4[0]), y(vec4[1]), z(vec4[2]) { }

	/* arithmetic operators */
	inline constexpr SHORTVECTOR3 operator+(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) { return SHORTVECTOR3(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z); }
	inline constexpr SHORTVECTOR3 operator-(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) { return SHORTVECTOR3(lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z); }
	inline constexpr SHORTVECTOR3 operator*(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) { return SHORTVECTOR3(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z); }
	inline constexpr SHORTVECTOR3 operator*(const SHORTVECTOR3& lhs, SHORT rhs)       { return SHORTVECTOR3(lhs.x*rhs,   lhs.y*rhs,   lhs.z*rhs  ); }
	inline constexpr SHORTVECTOR3 operator/(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) { return SHORTVECTOR3(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z); }
	inline constexpr SHORTVECTOR3 operator/(const SHORTVECTOR3& lhs, SHORT rhs)       { return SHORTVECTOR3(lhs.x/rhs,   lhs.y/rhs,   lhs.z/rhs  ); }

	/* assignment operators */
	SHORTVECTOR3& operator=(const SHORTVECTOR3& copy) {
		data[0] = copy.data[0];
		data[1] = copy.data[1];
		data[2] = copy.data[2];
		return *this;
	}
	SHORTVECTOR3& operator=(SHORT scalar)  {
		x = y = z = scalar;
		return *this;
	}
	SHORTVECTOR3& operator=(const __v4hi& vec4) { 
		data[0] = vec4[0];
		data[1] = vec4[1];
		data[2] = vec4[2];
		return *this;
	}
	inline constexpr SHORTVECTOR3& operator+=(const SHORTVECTOR3& rhs) { x+=rhs.x; y+=rhs.y; z+=rhs.z; return *this; }
	inline constexpr SHORTVECTOR3& operator-=(const SHORTVECTOR3& rhs) { x-=rhs.x; y-=rhs.y; z-=rhs.z; return *this; }
	inline constexpr SHORTVECTOR3& operator*=(const SHORTVECTOR3& rhs) { x*=rhs.x; y*=rhs.y; z*=rhs.z; return *this; }
	inline constexpr SHORTVECTOR3& operator*=(SHORT rhs)       { x*=rhs;   y*=rhs;   z*=rhs  ; return *this; }
	inline constexpr SHORTVECTOR3& operator/=(const SHORTVECTOR3& rhs) { x/=rhs.x; y/=rhs.y; z/=rhs.z; return *this; }
	inline constexpr SHORTVECTOR3& operator/=(SHORT rhs)       { x/=rhs;   y/=rhs;   z/=rhs  ; return *this; }

	/* array index operators */
	constexpr SHORT& operator[](size_t i) { return data[i]; }
	constexpr const SHORT& operator[](size_t i) const { return data[i]; }

	/* sign operators */
	inline SHORTVECTOR3 operator-() const { return SHORTVECTOR3(-x, -y, -z); }
	constexpr SHORTVECTOR3 operator+() const { return *this; }

	/* compare operators */
	inline constexpr bool operator==(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
	inline constexpr bool operator!=(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z; }

};

inline SHORTVECTOR3 floor(const SHORTVECTOR3& v) { return SHORTVECTOR3(floorf(v.x), floorf(v.y), floorf(v.z)); }
inline SHORTVECTOR3 ceil(const SHORTVECTOR3& v)	 { return SHORTVECTOR3(ceilf(v.x), ceilf(v.y), ceilf(v.z)); }

/* vector operations */
inline SHORTVECTOR3 cross(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) {
	SHORTVECTOR3 tmp[4] = { SHORTVECTOR3(lhs[1], lhs[2], lhs[0]), SHORTVECTOR3(rhs[1], rhs[2], rhs[0]) };

	tmp[2] = lhs * tmp[1] - rhs * tmp[0];

	tmp[3][2] = tmp[2][0];
	tmp[3][0] = tmp[2][1];
	tmp[3][1] = tmp[2][2];

	return tmp[3];
}
inline SHORT dot(const SHORTVECTOR3& lhs, const SHORTVECTOR3& rhs) { return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2]; }
inline SHORT norm(const SHORTVECTOR3& a) { return dot(a,a); }
inline SHORTVECTOR3 normalize(const SHORTVECTOR3& a) { return SHORTVECTOR3(a / norm(a)); }


