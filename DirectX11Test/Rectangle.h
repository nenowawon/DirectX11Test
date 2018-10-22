#pragma once

#include "MeshBase.h"
#include "vertex.h"

namespace Mesh {
	class Rectangle : public MeshBase
	{
	public:
		Rectangle();
		~Rectangle();

		Vertex m_pVertexArray[4] = {
			{ { -0.5f,  0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			{ {  0.5f,  0.5f, 0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
		};

		int m_IndexArray[6]{
			0, 1, 2,
			0, 3, 1,
		};

		virtual HRESULT Create(HWND hwnd);
		virtual void    Update();
		virtual void    Render(Transform* transform);
		virtual void    Release();
	};
}


