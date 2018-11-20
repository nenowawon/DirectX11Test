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
	// �I�u�W�F�N�g���쐬����
	for (auto gameObject : stageObjectArray) {
		DirectXRenderer::instance->AddGameObject(gameObject);
		gameObject->Create(hwnd);
	}
}
