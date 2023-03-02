#pragma once


#include "stdafx.h"


using namespace DirectX;

using namespace Microsoft::WRL;


class RenderPass
{
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
};

