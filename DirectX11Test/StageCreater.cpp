#include "stdafx.h"
#include "StageCreater.h"

#include "DirectXRenderer.h"

StageCreater::StageCreater()
{
}


StageCreater::~StageCreater()
{
}

void StageCreater::Create(HWND hwnd)
{
	// オブジェクトを作成する
	for (auto gameObject : stageObjectArray) {
		DirectXRenderer::instance->AddGameObject(gameObject);
		gameObject->Create(hwnd);
	}
}
