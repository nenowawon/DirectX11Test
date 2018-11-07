#pragma once
#include "MeshBase.h"

#include <string>

#include "ImageRenderer.h"

namespace Mesh
{
	class Sprite : public MeshBase
	{
	public:
		Sprite();
		~Sprite();

		float const oneSide = 0.5f;

		ImageVertex m_pVertexArray[4] = {
			{ { -oneSide,  oneSide, oneSide }, { 1.0f, 0.0f, 0.0f, 1.0f } ,{0.0f,1.0f}},
			{ {  oneSide, -oneSide, oneSide }, { 0.0f, 1.0f, 0.0f, 1.0f } ,{1.0f,0.0f}},
			{ { -oneSide, -oneSide, oneSide }, { 0.0f, 0.0f, 1.0f, 1.0f } ,{0.0f,0.0f}},
			{ {  oneSide,  oneSide, oneSide }, { 1.0f, 1.0f, 0.0f, 1.0f } ,{1.0f,1.0f}},
		};

		int m_IndexArray[6]{
			0, 1, 2,
			0, 3, 1,
		};
		

		virtual HRESULT Create(HWND hwnd,std::string filePath);
		virtual void    Update();
		virtual void    Render(Transform* transform);
		virtual void    Release();

	private:
		ImageRenderer* m_pImageRenderer;
	};
}


