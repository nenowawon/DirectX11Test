#pragma once

#include <directxmath.h>
#include <cmath>

struct Vertex
{
public:

	DirectX::XMFLOAT3 m_vertPos;

	DirectX::XMFLOAT4 m_vertColor;
};

struct ImageVertex
{
public:
	DirectX::XMFLOAT3 m_vertPos;
	DirectX::XMFLOAT4 m_vertColor;
	DirectX::XMFLOAT2 m_uvPos;
};

struct RectangleVertex
{
public:
	float width;
	float height;
	float left;
	float top;
	float right;
	float bottom;

	// �傫�����v�Z���A�����o�ϐ��ɐݒ肷��(��ɍ��W��ݒ肵�Ă�������)
	void CalcScale() {
		// ���̑傫����ݒ肷��
		width = std::abs(right-left);
		// �c�̑傫����ݒ肷��
		height = std::abs(top - bottom);
	};
};

