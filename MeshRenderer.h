#pragma once

#include "stdafx.h"

#include "Material.h"
#include "Mesh.h"

class MeshRenderer
{
public:
	MeshRenderer(Mesh* inMesh, Material* inMaterial) :m_Mesh(inMesh), m_Material(inMaterial) {};

public:
	//Now Is All Submesh Draw With One Material
	//Todo: Submesh Match Different Material
	Mesh* m_Mesh;
	Material* m_Material;

public: 
	D3D12_GRAPHICS_PIPELINE_STATE_DESC GetDrawingPSO();
};

