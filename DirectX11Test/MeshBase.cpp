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

void MeshBase::Release() 
{
	delete(m_meshRenderer);
}
