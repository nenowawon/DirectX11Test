#pragma once

#include "Collider.h"
#include <directxmath.h>

#include "GameObject.h"

#include "Vertex.h"

class RectangleCollider :
	public Collider
{
public:
	RectangleCollider();
	~RectangleCollider();

	//void Create(GameObject* object, Vertex(&vertexArray));

	void Create(GameObject* object, ImageVertex(&vertexArray)[4]);

	void Release();

	bool CheckCollider(RectangleCollider* collider);

	RECT GetRect();

private:

	void Create(GameObject* object);
	GameObject* m_pGameObject;
	RECT* m_pRect;
};

