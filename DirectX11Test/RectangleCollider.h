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

	bool CheckColliderTransform(RectangleCollider* collider,const Transform myTransform);

	RectangleVertex GetRect(Transform myTransform);

	GameObject* m_pGameObject;

private:

	void Create(GameObject* object);
	
	RectangleVertex* m_pRect;
};

