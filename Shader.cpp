#include "Shader.h"

Shader::Shader(std::string inShaderName, std::wstring shaderCsoFile, ShaderType InType)
{
	shaderName = inShaderName;
	Type = InType;
	D3DReadFileToBlob(shaderCsoFile.c_str(), &shaderByteCode);
	BuildShaderResources();

}

Shader::Shader(std::string inShaderName, std::wstring shaderPath, ShaderType InType, std::string enterName)
{
	Type = InType;
	shaderName = inShaderName;

	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;


	switch (InType)
	{
	case VertexShader:
		D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, enterName.c_str(), "vs_5_0", compileFlags, 0, &shaderByteCode, nullptr);
		break;
	case PixelShader:
		D3DCompileFromFile(shaderPath.c_str(), nullptr, nullptr, enterName.c_str(), "ps_5_0", compileFlags, 0, &shaderByteCode, nullptr);
		break;
	default:
		break;
	}

	BuildShaderResources();
}

void Shader::BuildShaderResources()
{
	shaderResources = {};
	shaderResources.pShaderBytecode = shaderByteCode->GetBufferPointer();
	shaderResources.BytecodeLength = shaderByteCode->GetBufferSize();
}