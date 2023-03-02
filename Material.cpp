#include "Material.h"

Material::Material()
{
	PSO = {};


}

void Material::SetupShader(Shader* inVertexShader, Shader* InPixelShader)
{
	VertexShader = inVertexShader;
	PixelShader = InPixelShader;
}

void Material::SetupInputLayout()
{
}

void Material::SetupRasterization()
{

}

void Material::SetupOutputState()
{

}

void Material::UpdatePSO()
{

}

void Material::CreateDefaultPSO(D3D12_GRAPHICS_PIPELINE_STATE_DESC& PSO)
{
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
	PSO.InputLayout = { inputElementDescs,0 };
	PSO.pRootSignature = nullptr;
	PSO.RasterizerState= CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	PSO.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	PSO.DepthStencilState.DepthEnable = FALSE;
	PSO.DepthStencilState.StencilEnable= FALSE;
	PSO.SampleMask = UINT_MAX;

	PSO.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	PSO.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	PSO.NumRenderTargets = 1;
	PSO.SampleDesc.Count = 1;

}
