#pragma once


#include "stdafx.h"
#include <vector>
#include "MeshRenderer.h"
#include "RendererViewport.h"

class RenderPass;

using namespace DirectX;

using namespace Microsoft::WRL;


class Renderer
{
public:
	Renderer();

public:
	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnDestroy();



public:
	void InitRendererResoruces();
	void CreateFence();
	//ViewPort
	RendererViewport* m_RenderWindow;

	//Í¬²½
	UINT m_frameIndex;
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_fence;
	UINT64 m_fenceValue;



public:
	//Method

//------------------Renderer Loop--------------------------------------

	//Logic Update
public:
	void Update();


	//Renderer Process
public:

	//Render Helper
	void EnqueRenderPass(RenderPass* RenderPass);

	//RenderProcess
	void Render();

	void InitalizedGlobalParamter();
	void Culling();
	void RenderProcess();
	void RendererExecute();
	void Present();
	void WaitRendererFrameEnd();




public:
	//Pass
	std::vector<RenderPass*> ExecutesPass;
	std::vector<MeshRenderer> RenderObject;


//Test Code
	void CreateTestMeshRenderer(std::wstring vsShaderPath, std::wstring psShaderPath);
	MeshRenderer* meshRenderer;
};

