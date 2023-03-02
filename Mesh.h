#pragma once

#include "stdafx.h"
#include <vector>

using namespace DirectX;
using namespace Microsoft::WRL;

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

struct SubMesh
{
	std::vector<Vertex> vertices;
	std::vector<UINT> indices;

	ComPtr<ID3D12Resource> vertexBuffer;
	ComPtr<ID3D12Resource> indexBuffer;
	ComPtr<ID3D12Resource> vBufferUploadHeap;
	ComPtr<ID3D12Resource> iBufferUploadHeap;

	UINT vBufferSize;
	UINT iBufferSize;
	UINT indexCount;

	D3D12_VERTEX_BUFFER_VIEW vBufferView;
	D3D12_INDEX_BUFFER_VIEW iBufferView;
};


class Mesh
{

	std::vector<SubMesh>	subMeshes;
	
public:
	void AddSubMesh(UINT meshIndex, Vertex* vertices, UINT vertexCount, UINT* indices, UINT indexCount);
	void RemoveSubMesh(UINT meshIndex);

	void CalulateTangents(UINT meshIndex);
	void CalulateNormal(UINT meshIndex);
	void CalulateSmoothNormal(UINT meshIndex);


	const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView(UINT index);
	const D3D12_INDEX_BUFFER_VIEW& GetIndexBufferView(UINT index);
	const UINT GetIndexCount(UINT index);
	const UINT						GetSubMeshCount();

public:
	static void InitalizedVertexBufferAndUploadBuffer(int bufferByteSize,  ID3D12Resource** defaultHeap, ID3D12Resource** uploadHeap, void* Data);
};

