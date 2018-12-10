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

	const float GROUND_POS_Y = -1.2f;

	const float LEFT_WALL_POS_X = -2.0f;

	GameObject* stageObjectArray[50] =
	{
		new Player(-0.1f,0.0f,0.0f),
		new MeshTest(),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y,0.0f),
		new SpriteTest(LEFT_WALL_POS_X + 0.2f,GROUND_POS_Y,0.0f),
		new SpriteTest(-1.6f,GROUND_POS_Y,0.0f),
		new SpriteTest(-1.4f,GROUND_POS_Y,0.0f),
		new SpriteTest(-1.2f,GROUND_POS_Y,0.0f),
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
		new SpriteTest(-0.3f,GROUND_POS_Y+0.8f,0.0f),
		new SpriteTest(-0.75f,GROUND_POS_Y + 0.8f,0.0f),
		new SpriteTest(-1.2f,GROUND_POS_Y + 0.8f,0.0f),
		new SpriteTest(-0.75f,GROUND_POS_Y + 1.4f,0.0f),
		new SpriteTest(0.45f,(GROUND_POS_Y + 1.2f),0.0f),
		//new SpriteTest(-0.55f,(GROUND_POS_Y + 0.3f),0.0f),
		new SpriteTest(1.2f,(GROUND_POS_Y + 0.2f),0.0f),
		new SpriteTest(1.4f,(GROUND_POS_Y + 0.2f),0.0f),
		new SpriteTest(1.2f,(GROUND_POS_Y + 0.4f),0.0f),
		new SpriteTest(1.4f,(GROUND_POS_Y + 0.4f),0.0f),
		new SpriteTest(1.2f,(GROUND_POS_Y + 0.6f),0.0f),
		new SpriteTest(1.4f,(GROUND_POS_Y + 0.6f),0.0f),
		new SpriteTest(0.8f,GROUND_POS_Y,0.0f),
		new SpriteTest(1.0f,GROUND_POS_Y,0.0f),
		new SpriteTest(1.2f,GROUND_POS_Y,0.0f),
		new SpriteTest(1.4f,GROUND_POS_Y,0.0f),
		new SpriteTest(1.6f,GROUND_POS_Y,0.0f),
		new SpriteTest(1.8f,GROUND_POS_Y,0.0f),
		new SpriteTest(2.0f,GROUND_POS_Y,0.0f),
		new SpriteTest(2.0f,GROUND_POS_Y+0.2f,0.0f),
		new SpriteTest(2.0f,GROUND_POS_Y + 0.4f,0.0f),
		new SpriteTest(2.2f,GROUND_POS_Y,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 0.2f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 0.4f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 0.6f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 0.8f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 1.0f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 1.2f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 1.4f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 1.6f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 1.8f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 2.0f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 2.2f ,0.0f),
		new SpriteTest(LEFT_WALL_POS_X,GROUND_POS_Y + 2.4f ,0.0f),
	};
};

