#pragma once
#include "stdafx.h"




using namespace DirectX;

using namespace Microsoft::WRL;

class RendererViewport
{

public:
	RendererViewport();


	void SwapChainBufferIndex();
	ID3D12Resource* GetCurrentSwapChainRenderTarget() { return renderTargets[frameIndex].Get(); }
	INT  GetCurrentSwapChainRenderTargetIndex() { return frameIndex; }

protected:
	void CreateSwanChain();
	void SetupRendererViewport();



public:
	static const UINT FrameCount = 2;
	CD3DX12_VIEWPORT viewport;
	CD3DX12_RECT scissorRect;
	ComPtr<IDXGISwapChain3> swapChain;

	int frameIndex;
	//ForwardRednerer
	ComPtr<ID3D12Resource> renderTargets[FrameCount];


	int rtvDescriptorSize;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;

};

