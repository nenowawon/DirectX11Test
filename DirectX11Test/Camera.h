#pragma once

#include "Vertex.h"

class Camera
{
public:
	Camera();
	~Camera();

	DirectX::XMFLOAT3    m_pos;
	DirectX::XMFLOAT3    m_rotation;
};

