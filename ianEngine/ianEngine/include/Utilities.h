#pragma once
#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "GLlog.h"

#include "MathLibrary.h"
#include "TextFileReader.h"
#include <SOIL.h>

#include <vector>
#include <map>

struct Vec2
{
	Vec2();
	Vec2(float x, float y);

	void operator = (const Vec2& a_rVecSource);

	float fX, fY;
};

struct Vertex
{	union
	{	struct
		{	Vector3 Pos;
			Vector4 Color;
			Vec2 UV;};
		struct
		{	float X, Y, Z;
			float R, G, B, A;
			float U, V; 
		};};
	bool operator == (const Vertex& rhs){
		return (X == rhs.X && Y == rhs.Y && Z == rhs.Z
				&& R == rhs.R && G == rhs.G && B == rhs.B && A == rhs.A
				&& U == rhs.U && V == rhs.V);
	}};

//struct UV
//{
//	float Umin, Vmin, Umax, Vmax;
//};

extern Matrix4 * Ortho;

// keep track of window size for things like the viewport and the mouse cursor
extern int g_gl_width;
extern int g_gl_height;

enum AnimCycle
{
	ONCE,
	LOOP, 
	LOOPSECTION,
	PINGPONG,
	REVERSE,
	RANDOM,
	SINGLE
};

void Orthographic(float a_fLeft, float a_fRight, float a_fTop, float a_fBottom, 
				  float a_fNear, float a_fFar, Matrix4 * mat);

#endif