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

		virtual HRESULT Create(HWND hwnd) = 0;
		virtual void    Update() = 0;
		virtual void    Render(Transform* transform) = 0;
		virtual void    Release() = 0;

	protected:
		MeshRenderer* m_meshRenderer;
	};
}


