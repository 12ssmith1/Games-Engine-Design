#include "object3DS.h"
#include "../gl/glut.h"
#include "3dsLoader.h"
#include "GameScreenLevel1.h"
#include "Texture.h"
#include "Commons.h"
#include "Constants.h"
#include "object3DS.h"

Object3DS::Object3DS(Vertex3D startPosition, string modelFileName, Vertex3D startRot)
{
	//start position.
	mPosition = startPosition;
	mRotate = startRot;
	
	
	//3ds file to load
	std::strcpy(filename, modelFileName.c_str());
		loadModel();
		
}

void Object3DS::InitValues()
{
	UfoRotSpeed = 0.0f;
	UfoRot = 0.0f;
}

void Object3DS::loadModel()
{
	if (filename[0] != '---')
		Load3DS(&object, filename);
}



void Object3DS::render()
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);

	glRotatef(-UfoRot, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (Triangles)

	for (int l_index = 0; l_index < object.triangle_qty; l_index++)
	{
							 
			//Texture coordinates of the first vertex
			glTexCoord2f(object.texcoord[object.triangle[l_index].a].u,
						object.texcoord[object.triangle[l_index].a].v);
					

		glVertex3f(object.vertex[object.triangle[l_index].a].x,
				object.vertex[object.triangle[l_index].a].y,
				object.vertex[object.triangle[l_index].a].z); // Vertex Definition

					

			//Texture coordinates of the first vertex
			glTexCoord2f(object.texcoord[object.triangle[l_index].b].u,
						object.texcoord[object.triangle[l_index].b].v);
						
		
		glVertex3f(object.vertex[object.triangle[l_index].b].x,
			object.vertex[object.triangle[l_index].b].y,
			object.vertex[object.triangle[l_index].b].z);
		
				

			//Texture coordinates of the first vertex
			glTexCoord2f(object.texcoord[object.triangle[l_index].c].u,
						object.texcoord[object.triangle[l_index].c].v);
						

		glVertex3f(object.vertex[object.triangle[l_index].c].x,
			object.vertex[object.triangle[l_index].c].y,
			object.vertex[object.triangle[l_index].c].z);
	}
	
	glEnd();

	glPopMatrix();

}

void Object3DS::update(float deltaTime)
{

	if (reached == false)
	{
		mPosition.x += 0.1f;

		if (mPosition.x >= 500.0)
		{
			reached = true;
		}
	}
		
	if (reached == true)

	{
		mPosition.x -= 0.1f;

		if (mPosition.x <= -10.0)
		{
			reached = false;
		}
	}

	UfoRot += UfoRotSpeed;

	if (UfoRot >=360.0f)
	{
		UfoRot = 0.0f;
	}

	
	

	glTranslatef(mPosition.x, mPosition.y, mPosition.z);

	//rotation = 90.0;
	//glRotatef(90.0f, mRotate.x, mRotate.y, mRotate.z +90);
}

void Object3DS::SetUfoSpeed(float speed)
{
	UfoRotSpeed = speed;
}