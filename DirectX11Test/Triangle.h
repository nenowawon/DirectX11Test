#pragma once


#include "GameObject.h"

#include "vertex.h"

namespace Mesh {
	class Triangle : public GameObject
	{

	public:
		Triangle();
		~Triangle();

		Vertex m_pVertexArray[3] = {
			{ { -0.5f,  0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
		};

		virtual HRESULT Create(HWND hwnd);
		virtual void    Update();
		virtual void    Render();
		virtual void    Release();
	};
}