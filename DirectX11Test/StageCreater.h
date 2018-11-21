#pragma once
#include "GameObject.h"
#include "Player.h"
#include "MeshTest.h"
#include "SpriteTest.h"

class StageCreater
{
public:
	StageCreater();
	~StageCreater();

	void Create(HWND hwnd);

	const float GROUND_POS_Y = -0.6f;

	GameObject* stageObjectArray[18] = 
	{
		new Player(-0.1f,0.0f,0.0f),
		new MeshTest(),
		new SpriteTest(-1.0f,GROUND_POS_Y,0.0f),
		new SpriteTest(-0.8f,GROUND_POS_Y,0.0f),
		new SpriteTest(-0.6f,GROUND_POS_Y,0.0f),
		new SpriteTest(-0.4f,GROUND_POS_Y,0.0f),
		new SpriteTest(-0.4f,GROUND_POS_Y,0.0f),
		new SpriteTest(-0.2f,GROUND_POS_Y,0.0f),
		new SpriteTest(0.0f,GROUND_POS_Y,0.0f),
		new SpriteTest(0.2f,GROUND_POS_Y,0.0f),
		new SpriteTest(0.4f,GROUND_POS_Y,0.0f),
		new SpriteTest(0.6f,GROUND_POS_Y,0.0f),
		new SpriteTest(-0.35f,0.0f,0.0f),
		new SpriteTest(-0.35f,0.2f,0.0f),
		new SpriteTest(-0.55f,0.2f,0.0f),
		new SpriteTest(0.25f,(GROUND_POS_Y+0.2f),0.0f),
		new SpriteTest(-0.55f,(GROUND_POS_Y + 0.3f),0.0f),
		new SpriteTest(0.8f,(GROUND_POS_Y + 0.3f),0.0f),
	};
};

