#include "stdafx.h"
#include "RectangleCollider.h"
#include "DirectXRenderer.h"

using namespace DirectX;

RectangleCollider::RectangleCollider():
	m_pGameObject(nullptr),
	m_pRect(nullptr)
{
}


RectangleCollider::~RectangleCollider()
{
	Release();
}

void RectangleCollider::Create(GameObject* object, ImageVertex(&vertexArray)[4]) {

	Create(object);

	float min_x = 0;
	float max_x = 0;

	float min_y = 0;
	float max_y = 0;

	int size = sizeof(vertexArray) / sizeof(ImageVertex);

	for (size_t i = 0; i < sizeof(vertexArray) / sizeof(ImageVertex); i++)
	{
		// x座標の最大値を更新する
		if (vertexArray[i].m_vertPos.x > max_x) {
			max_x = vertexArray[i].m_vertPos.x;
		}

		// x座標の最小値を更新する
		if (vertexArray[i].m_vertPos.x < min_x) {
			min_x = vertexArray[i].m_vertPos.x;
		}

		// y座標の最大値を更新する
		if (vertexArray[i].m_vertPos.y > max_y) {
			max_y = vertexArray[i].m_vertPos.y;
		}

		// y座標の最小値を更新する
		if (vertexArray[i].m_vertPos.y < min_y) {
			min_y = vertexArray[i].m_vertPos.y;
		}
	}
	// 左辺の座標を設定
	m_pRect->left = min_x;
	// 右辺の座標を設定
	m_pRect->right = max_x;

	// 上辺の座標を設定
	m_pRect->top = max_y;
	// 下辺の座標を設定
	m_pRect->bottom = min_y;

	m_pRect->CalcScale();
}

void RectangleCollider::Create(GameObject* object) {
	m_pGameObject = object;
	m_pRect = new RectangleVertex();
	DirectXRenderer::instance->AddCollider(this);
}

void RectangleCollider::Release() {
	DirectXRenderer::instance->RemoveCollider(this);
	delete(m_pRect);
}

bool RectangleCollider::CheckCollider(RectangleCollider * collider)
{
	
	return CheckColliderTransform(collider,*m_pGameObject->m_pTransform);
}

bool RectangleCollider::CheckColliderTransform(RectangleCollider * collider, const Transform myTransform)
{

	// 自分のコライダー
	RectangleVertex myRect = GetRect(myTransform);

	// チェック相手のコライダー	
	RectangleVertex checkRect = collider->GetRect(*(collider->m_pGameObject->m_pTransform));

	//横に重なっていた場合
	if (myRect.left <= checkRect.right && myRect.right >= checkRect.left)
	{

		//縦に重なっていた場合
		if (myRect.top >= checkRect.bottom && myRect.bottom <= checkRect.top)
		{
			return true;
		}

	}
	return false;
}

RectangleVertex RectangleCollider::GetRect(Transform myTransform)
{
	RectangleVertex rect = RectangleVertex();

	// 頂点座標をワールド座標に変換する
	// 左
	rect.left = (myTransform.m_pos.x) + (m_pRect->left);
	// 上
	rect.top = (myTransform.m_pos.y) + (m_pRect->top);
	// 右
	rect.right = (myTransform.m_pos.x) + (m_pRect->right);
	// 下
	rect.bottom = (myTransform.m_pos.y) + (m_pRect->bottom);

	return rect;
}
