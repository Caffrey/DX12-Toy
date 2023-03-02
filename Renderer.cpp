#include "Renderer.h"
#include "DynamicRHI.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"


Renderer::Renderer()
{
	InitRendererResoruces();
}

void Renderer::OnInit()
{
}

void Renderer::OnUpdate()
{
}

void Renderer::OnRender()
{
}

void Renderer::OnDestroy()
{
	CloseHandle(m_fenceEvent);
}

void Renderer::InitRendererResoruces()
{
	m_RenderWindow = new RendererViewport();
	CreateFence();
}

void Renderer::CreateFence()
{
	auto Device = DynamicRHI::Instance()->Device;

	auto hr = Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
	m_fenceValue = 1;

	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	


}

void Renderer::Update()
{
}

void Renderer::EnqueRenderPass(RenderPass* RenderPass)
{

}

void Renderer::Render()
{
	InitalizedGlobalParamter();
	Culling();
	RenderProcess();
	RendererExecute();
	Present();
	WaitRendererFrameEnd();

}

void Renderer::InitalizedGlobalParamter()
{
}

void Renderer::Culling()
{
}

void Renderer::RenderProcess()
{
}

void Renderer::RendererExecute()
{
}

void Renderer::Present()
{
	m_RenderWindow->swapChain->Present(1, 0);
}

void Renderer::WaitRendererFrameEnd()
{
	const UINT64 fence = m_fenceValue;

	auto commandQueue = DynamicRHI::Instance()->CommandQueue;
	commandQueue->Signal(m_fence.Get(), fence);
	m_fenceValue++;

	if (m_fence->GetCompletedValue() < fence)
	{
		m_fence->SetEventOnCompletion(fence, m_fenceEvent);
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}

	m_RenderWindow->SwapChainBufferIndex();

}

void Renderer::CreateTestMeshRenderer(std::wstring vsShaderPath, std::wstring psShaderPath)
{
	//create shader
	Shader* vsShader = new Shader("vsShader", vsShaderPath, ShaderType::VertexShader);
	Shader* psShader = new Shader("psShader", psShaderPath, ShaderType::PixelShader);

	float AspectRatio = DynamicRHI::Instance()->AspectRatio;
	//create vertex
	Vertex triangleVertices[] =
	{
		{ { 0.0f, 0.25f * AspectRatio, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 0.25f, -0.25f * AspectRatio, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.25f, -0.25f * AspectRatio, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};
	UINT Indices[] = {0,1,2};
	Mesh* mesh = new Mesh();
	mesh->AddSubMesh(0, triangleVertices, 3, Indices, 3);


	Material* mat = new Material();
	mat->SetupShader(vsShader, psShader);

	meshRenderer = new MeshRenderer(mesh, mat);

}
