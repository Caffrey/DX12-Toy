#pragma once

#include "stdafx.h"
#include <string.h>


using namespace DirectX;
using Microsoft::WRL::ComPtr;


enum ShaderType
{
	VertexShader,
	PixelShader,
};
class Shader
{
public:
	std::string shaderName;

	Shader(std::string inShaderName, std::wstring shaderCsoFile, ShaderType InType);
	Shader(std::string inShaderName, std::wstring shaderPath, ShaderType inType, std::string enterName);
	~Shader() {}

	D3D12_SHADER_BYTECODE GetShaderResources() { return shaderResources; }
protected:

	ComPtr<ID3DBlob> shaderByteCode;
	ShaderType Type;
	D3D12_SHADER_BYTECODE shaderResources;

private:
	void BuildShaderResources();
};



class ShaderManager
{

};