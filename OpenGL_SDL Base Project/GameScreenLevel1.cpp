#include "GameScreenLevel1.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"
#include "Texture.h"
#include "object3DS.h"
#include "Camera.h"
#include <string>
#include <sstream>

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel1::GameScreenLevel1() : GameScreen()
{
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	//clear background colour.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	


	Vertex3D startPosition;
	startPosition.x = 0.0f;
	startPosition.y = 0.0f;
	startPosition.z = 0.0f;

	Vertex3D startRot;
	startRot.x = 0.0f;
	startRot.y = 0.0f;
	startRot.z = 0.0f;

	UFO = new Object3DS(startPosition, "UFO.3DS", startRot);
	UFO->SetUfoSpeed(17.0f);
	BG = new Object3DS(startPosition, "BG.3DS", startRot);
	Moon = new Object3DS(startPosition, "Moon.3DS", startRot);
	camInstance = new Camera;


	pyramid = new Pyramid();
	//rotation = 30.0f;

	Texture2D* stars = new Texture2D();
	stars->Load("stars.raw", 7760, 4938);
	Texture2D* moon = new Texture2D();
	moon->Load("UFO.raw", 640, 240);
	Texture2D* ufo = new Texture2D();
	ufo->Load("ship.raw", 512, 512);
	
	dui = 999;
	
	

	//texture->Load("Penguins.raw", 512, 512);
	// texture stuff
	
		


}


//--------------------------------------------------------------------------------------------------

GameScreenLevel1::~GameScreenLevel1()
{	
}

//--------------------------------------------------------------------------------------------------
void GameScreenLevel1::OutputLine(float x, float y, string text)

{
	glRasterPos2f(x, y);            //Pos to start drawing
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
	}
}


void GameScreenLevel1::SetLight(){
	lighting light = {
		{1.0f,1.0f,1.0f,1.0f},
		{0.7f,0.7f,0.7f,1.0f},
		{0.5f, 0.5f,0.5f,1.0f}
	};
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

}

void GameScreenLevel1::SetMaterial(){
	material material = {
		{ 1.00f, 1.00f, 1.00f, 1.0f },
		{ 1.00f, 1.00f, 1.00f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		0.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material.specualr);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}


void GameScreenLevel1::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	/*glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f,
		      0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);*/
	
	glScalef(0.5f, 0.5f, 0.5f);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 1);
	BG->render();
	
	
	glBindTexture(GL_TEXTURE_2D, 2);
	Moon->render();

	
	glBindTexture(GL_TEXTURE_2D, 3);
	UFO->render();


	SetLight();
	SetMaterial();
	
	camInstance->Render();

	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	OutputLine(5, 95, "USE WASD TO MOVE CAMERA AND ZOOM, USE ARROW KEYS TO ROTATE THE CAMERA");
	OutputLine(5, 85, "PRESS 'Z' TO BRING ANNIHILATION CLOSER!!!");
	int score = 25;
	float health = 0.75;
	stringstream ss;
	ss << "Days until invasion:  " << dui << endl;
	OutputLine(5, 90, ss.str());
	int dui = 300;
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	
	
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;
	//rotation += 40.0f;

	UFO->update(deltaTime);
	
	
	camInstance->Update(deltaTime, e);

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_z:
			//move forwards
			dui -= 1;
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------------
