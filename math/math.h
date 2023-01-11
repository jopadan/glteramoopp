#pragma once
#include <cmath>

enum vector_index
{
	ourX = 0,
	ourY = 1,
	ourZ = 2,
	ourW = 3
};

enum color_bgra
{
	ourR = 2,
	ourG = 1,
	ourB = 0,
	ourA = 3,
}

#define	EPS			1e-7
#define	D2R(x)			( ( x ) * ( 1.0F / 57.2957F) )		/* Nick Pelling changed */
#define	R2D(x)			( ( x ) * 57.2957F )
#define	SINR(x)			sinf( x )
#define	COSR(x)			cosf( x )
#define	SIND(x)			( sinf( D2R( x ) ) )
#define	COSD(x)			( cosf( D2R( x ) ) )
#define ATAND(y, x)		R2D( atan2f(y, x) )
#define FMOD( NUM, DIV )	( (NUM) - (DIV) * ( floorf( (NUM) / (DIV) ) ) )
#define FDIV( NUM, DIV )	( (DIV) * ( floorf( (NUM) / (DIV) ) ) )


typedef struct
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} rect_t;

typedef struct
{
    long  x;
    long  y;
} point_t;

