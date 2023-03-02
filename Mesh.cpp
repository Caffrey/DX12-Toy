#include "Mesh.h"
#include "DynamicRHI.h"

void Mesh::AddSubMesh(UINT meshIndex, Vertex* vertices, UINT vertexCount, UINT* indices, UINT indexCount)
{
	//build sub mesh 

	SubMesh subMesh;

	subMesh.indexCount = indexCount;
	subMesh.vBufferSize = sizeof(Vertex) * vertexCount;
	subMesh.iBufferSize = sizeof(UINT) * indexCount;

	subMesh.vertices.assign(vertices, vertices + vertexCount);
	subMesh.indices.assign(indices, indices + indexCount);

	InitalizedVertexBufferAndUploadBuffer(subMesh.vBufferSize, subMesh.vertexBuffer.GetAddressOf(), subMesh.vBufferUploadHeap.GetAddressOf(), subMesh.vertices.data());
	InitalizedVertexBufferAndUploadBuffer(subMesh.iBufferSize, subMesh.indexBuffer.GetAddressOf(), subMesh.iBufferUploadHeap.GetAddressOf(), subMesh.indices.data());

	subMesh.vBufferView.BufferLocation = subMesh.vertexBuffer->GetGPUVirtualAddress();
	subMesh.vBufferView.StrideInBytes = sizeof(Vertex);
	subMesh.vBufferView.SizeInBytes = subMesh.vBufferSize;

	subMesh.iBufferView.BufferLocation = subMesh.indexBuffer->GetGPUVirtualAddress();
	subMesh.iBufferView.Format = DXGI_FORMAT_R32_UINT;
	subMesh.iBufferView.SizeInBytes = subMesh.iBufferSize;
	//build buffer view

	subMeshes.push_back(subMesh);
}

void Mesh::RemoveSubMesh(UINT meshIndex)
{
	
}

void Mesh::CalulateTangents(UINT meshIndex)
{

}

void Mesh::CalulateNormal(UINT meshIndex)
{

}

void Mesh::CalulateSmoothNormal(UINT meshIndex)
{

}

const D3D12_VERTEX_BUFFER_VIEW& Mesh::GetVertexBufferView(UINT index)
{
	return subMeshes[index].vBufferView;

}

const D3D12_INDEX_BUFFER_VIEW& Mesh::GetIndexBufferView(UINT index)
{
	return subMeshes[index].iBufferView;
}

const UINT Mesh::GetIndexCount(UINT index)
{
	return (UINT)subMeshes.size();
}

const UINT Mesh::GetSubMeshCount()
{
	return 0;
}

void Mesh::InitalizedVertexBufferAndUploadBuffer(int bufferByteSize, ID3D12Resource** defaultHeap, ID3D12Resource** uploadHeap, void* Data)
{

	ComPtr<ID3D12Device> device = DynamicRHI::Instance()->Device;
	ComPtr<ID3D12GraphicsCommandList> cmdList = DynamicRHI::Instance()->commandlist;


	auto hr=  device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferByteSize),
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr, IID_PPV_ARGS(defaultHeap));

	hr = device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferByteSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(uploadHeap));


	D3D12_SUBRESOURCE_DATA subResData = {};
	subResData.pData = reinterpret_cast<BYTE*>( Data);
	subResData.RowPitch = bufferByteSize;
	subResData.SlicePitch = bufferByteSize;

	UpdateSubresources(cmdList.Get(), *defaultHeap, *uploadHeap, 0, 0, 1,&subResData);
	cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(*defaultHeap, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER));

}
