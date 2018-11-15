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

	RectangleVertex GetRect();

	GameObject* m_pGameObject;

private:

	void Create(GameObject* object);
	
	RectangleVertex* m_pRect;
};

