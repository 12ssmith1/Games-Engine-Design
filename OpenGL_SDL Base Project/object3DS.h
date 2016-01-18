#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_

#include "Commons.h"
#include <string>
using std::string;

class Object3DS
{
public:
	Object3DS(Vertex3D startPosition, string modelFileName, Vertex3D startRot );
	
	~Object3DS(){}

	void update(float deltaTime);
	void render();
	void SetUfoSpeed(float speed);
	void InitValues();

	//Load 3ds file
	void loadModel();

	//Load texture for this model.
	void loadTexture();

private:
	Vertex3D mPosition;
	Vertex3D mRotate;
	int texture;
	char filename[20];
	char textureName[20];

	obj_type object;

	bool reached = false;
	bool spin = true;
	float posX;
	float posY;
	float posZ;
	float UfoRotSpeed;
	float UfoRot;

};
#endif //_OBJECT3DS_H_