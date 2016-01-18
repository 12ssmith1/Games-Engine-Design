#ifndef _PYRAMID_H
#define _PYRAMID_H

#include <Windows.h> // Required to run OpenGL Windows
#include <gl/GL.h> // This is OpenGL
#include<gl/GLU.h> // This is OpenGLs Utilities 
#include "Commons.h" 

class Pyramid
{
private:
	Vertex3D * indexedVertices;
	short * indices;

	int numVerticies;
	int IndexCount;

	bool Load(char* path);
	void DrawTriangle(short a, short b, short c);

public:
	Pyramid(void);
	~Pyramid(void);

	void Draw(void);
	void Update(void);

};

#endif


