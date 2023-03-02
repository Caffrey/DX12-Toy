#pragma once

#include "stdafx.h"

using namespace DirectX;
using namespace Microsoft::WRL;

//Now Is Only Fix ColorRenderTarget
class RenderTarget
{
public:
	RenderTarget() {};





protected:
	ComPtr<ID3D12Resource> m_RenderTargetTexture;
};

