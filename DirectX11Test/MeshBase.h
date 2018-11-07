#pragma once

#include "vertex.h"

#include "Transform.h"

#include "MeshRenderer.h"
//class MeshRenderer;

namespace Mesh 
{
	class MeshBase
	{
	public:
		MeshBase();
		~MeshBase();

		virtual HRESULT Create(HWND hwnd);
		virtual void    Update() = 0;
		virtual void    Render(Transform* transform) = 0;
		virtual void    Release() = 0;

	protected:

		//Vertex m_pVertexArray[4];

		MeshRenderer* m_meshRenderer;
	};
}


