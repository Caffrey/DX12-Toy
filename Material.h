#pragma once



#include "stdafx.h"
#include "Shader.h"
#include "Texture.h"

class Material
{

public:
	Material();
	
	void SetupShader(Shader* inVertexShader, Shader* InPixelShader);
	void SetupInputLayout();


	void SetupRasterization();
	void SetupOutputState();

protected:
	Shader* VertexShader;
	Shader* PixelShader;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC PSO; 


	void UpdatePSO();

	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;

	D3D12_INPUT_ELEMENT_DESC VertexInputLayout[];



	static void CreateDefaultPSO(D3D12_GRAPHICS_PIPELINE_STATE_DESC& PSO);
};

