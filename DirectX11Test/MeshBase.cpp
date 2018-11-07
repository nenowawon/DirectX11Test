#include "stdafx.h"
#include "MeshBase.h"

using namespace Mesh;

MeshBase::MeshBase():
	m_meshRenderer(nullptr)
{
	m_meshRenderer = new MeshRenderer();
}

MeshBase::~MeshBase()
{
	Release();
}

HRESULT Mesh::MeshBase::Create(HWND hwnd)
{
	return E_NOTIMPL;
}



void MeshBase::Release() 
{
	delete(m_meshRenderer);
}
