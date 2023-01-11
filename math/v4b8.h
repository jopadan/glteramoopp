#pragma once
#include "vector.h"

template<>
struct vec<GLubyte, 4>
{
	union {
		std::array<GLubyte, 4> data;
		struct { GLubyte x, y, z, w; };
		struct { GLubyte r, g, b, a; };
		struct { GLubyte u, v, s, t; };
		vec<GLubyte, 3> xyz;
		vec<GLubyte, 3> rgb;
		struct { vec<GLubyte, 2> low, high; };
	};
	vec<GLubyte, 4>() = default;
	vec<GLubyte, 4>(GLubyte _x, GLubyte _y, GLubyte _z, GLubyte _w) : x(_x), y(_y), z(_z), w(_w) { }
	vec<GLubyte, 4>(__v4b v) { *(__v4b*)data.begin() = v; }
	__v4b operator (__v4b) { return *(__v4b*)data.begin(); }
};
