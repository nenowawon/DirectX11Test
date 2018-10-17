#pragma once

#include "GameObject.h"
#include "vertex.h"

namespace Mesh {
	class Cube : public GameObject
	{
	public:
		Cube();
		~Cube();

		float const oneSide = 0.5f;

		Vertex m_pVertexArray[8] = {
			{ { -oneSide, -oneSide,  oneSide }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  oneSide, -oneSide,  oneSide }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  oneSide, -oneSide, -oneSide }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { -oneSide, -oneSide, -oneSide }, { 1.0f, 0.0f, 0.0f, 1.0f } },

			{ { -oneSide,  oneSide,  oneSide }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			{ {  oneSide,  oneSide,  oneSide }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			{ {  oneSide,  oneSide, -oneSide }, { 0.0f, 1.0f, 1.0f, 1.0f } },
			{ { -oneSide,  oneSide, -oneSide }, { 0.0f, 1.0f, 1.0f, 1.0f } },
		};

		int m_IndexArray[36]{
			0, 2, 1,
			0, 3, 2,

			0, 5, 4,
			0, 1, 5,

			1, 6, 5,
			1, 2, 6,

			2, 7, 6,
			2, 3, 7,

			0, 4, 7,
			0, 7, 3,

			4, 5, 7,
			5, 6, 7,
		};

		virtual HRESULT Create(HWND hwnd);
		virtual void    Render();
		virtual void    Release();
	};
}

