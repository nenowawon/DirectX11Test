#include "stdafx.h"
#include "RectangleCollider.h"

using namespace DirectX;

RectangleCollider::RectangleCollider():
	m_pGameObject(nullptr)
{
	
}


RectangleCollider::~RectangleCollider()
{
	Release();
}

//void RectangleCollider::Create(GameObject* object, Vertex(&vertexArray) ) {
//	
//	Create(object);
//	float min_x = 0;
//	float max_x = 0;
//
//	float min_y = 0;
//	float max_y = 0;
//
//	for (size_t i = 0; i < sizeof(vertexArray)/sizeof(Vertex); i++)
//	{
//
//	}
//}

void RectangleCollider::Create(GameObject* object, ImageVertex(&vertexArray)[4]) {

	Create(object);
	float min_x = 0;
	float max_x = 0;

	float min_y = 0;
	float max_y = 0;

	int size = sizeof(vertexArray) / sizeof(ImageVertex);

	for (size_t i = 0; i < sizeof(vertexArray) / sizeof(ImageVertex); i++)
	{

	}
}

void RectangleCollider::Create(GameObject* object) {
	m_pGameObject = object;
}

void RectangleCollider::Release() {
}

bool RectangleCollider::CheckCollider(RectangleCollider * collider)
{
	RECT rect = collider->GetRect();
	RECT myRect = GetRect();

	return false;
}

RECT RectangleCollider::GetRect()
{
	RECT rect = RECT();
	/*rect.left = posX - m_scale->x / 2;
	rect.top = posY - m_scale->y / 2;
	rect.right = posX + m_scale->x / 2;
	rect.bottom = posY + m_scale->y / 2;*/

	return rect;
}
