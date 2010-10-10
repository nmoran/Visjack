#ifndef _UTIL_H_
#define _UTIL_H_

#include <math.h>
#include <stdio.h>   
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <SDL/SDL.h>
#include <SDL.h>
//#include "SDL/SDL_main.h"
#include "SDL_main.h"
#include <SDL/SDL_image.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#endif

#include <iostream>

using namespace std; 

#define PI 3.1415926535
#define ROTSPEED 100.0
#define FORCE 500.0
#define RESISTANCE 0.5


class VECTOR {
public :
	float x;
	float y;
	float z;
	VECTOR ( )
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}
	VECTOR( float X , float Y , float Z )
	{
		x = X;
		y = Y;
		z = Z;
	}
	VECTOR operator+(VECTOR a)
	{
		return VECTOR(a.x + x, a.y + y, a.z + z);
	}

	VECTOR operator-(VECTOR a)
	{
		return VECTOR(x - a.x, y - a.y, z - a.z);
	}
	
	VECTOR operator*(float num)
	{
		return VECTOR(x * num, y * num, z * num);
	}

	VECTOR operator/(float num)
	{
		return VECTOR(x / num, y / num, z / num);
	}

	void set( float X , float Y , float Z )
	{
		x = X;
		y = Y;
		z = Z;
	}
	
	float magnitude(  )
	{
		return sqrt ( this->x * this->x + this->y * this->y + this->z * this->z );
	}
};

float vector_magnitude(VECTOR a);


class POLYGON {
public :
	int num_vertices;
	VECTOR* vertices;
	VECTOR normal;
};


#endif
