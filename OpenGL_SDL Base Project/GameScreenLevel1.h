#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <SDL.h>
#include "GameScreen.h"
#include "Pyramid.h"
#include "object3DS.h"
#include "Camera.h"

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1();
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void SetLight();
	void SetMaterial();
	void OutputLine(float x, float y, string text);
	void Timer();
	int dui;
//--------------------------------------------------------------------------------------------------
private:
	
	float mCurrentTime;
	Pyramid * pyramid;
	float rotation;
	Object3DS* UFO;
	Object3DS* BG;
	Object3DS* Moon;
	Camera* camInstance;
	bool textured = false;
	


};


#endif //_GAMESCREENLEVEL1_H