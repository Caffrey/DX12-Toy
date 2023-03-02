#include "RendererViewport.h"
#include "DynamicRHI.h"
#include "Win32Application.h"

void RendererViewport::SetupRendererViewport()
{
	CreateSwanChain();
	int width = DynamicRHI::Instance()->ScreenWidth;
	int height = DynamicRHI::Instance()->ScreenHeight;
	viewport = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height));
	scissorRect = CD3DX12_RECT(0, 0, static_cast<LONG>(width), static_cast<LONG>(height));
}

RendererViewport::RendererViewport()
{
	SetupRendererViewport();
}

void RendererViewport::SwapChainBufferIndex()
{
	frameIndex = swapChain->GetCurrentBackBufferIndex();
}

void RendererViewport::CreateSwanChain()
{
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};

	swapChainDesc.BufferCount = FrameCount;// use double ring buffer;
	swapChainDesc.Width = DynamicRHI::Instance()->ScreenWidth;
	swapChainDesc.Height = DynamicRHI::Instance()->ScreenHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;


	ComPtr<IDXGISwapChain1> TempswapChain;
	auto factory = DynamicRHI::Instance()->factory;

	HRESULT hr;
	hr = factory->CreateSwapChainForHwnd(
		DynamicRHI::Instance()->CommandQueue.Get(),
		Win32Application::GetHwnd(),
		&swapChainDesc,
		nullptr, nullptr,
		&TempswapChain
	);

	hr = factory->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWA_NO_ALT_ENTER);
	TempswapChain.As(&swapChain);
	frameIndex = swapChain->GetCurrentBackBufferIndex();


	//create rvt desc heap
	D3D12_DESCRIPTOR_HEAP_DESC rvtHeapDesc = {};
	rvtHeapDesc.NumDescriptors = FrameCount;
	rvtHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rvtHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	hr = DynamicRHI::Instance()->Device->CreateDescriptorHeap(&rvtHeapDesc, IID_PPV_ARGS(&rtvHeap));
	rtvDescriptorSize = DynamicRHI::Instance()->Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// Create frame resources.
	CD3DX12_CPU_DESCRIPTOR_HANDLE rvtHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT n = 0; n < FrameCount; n++)
	{
		//create rendertarget buffer already with screen need format , data detial in swapchian desc below
		swapChain->GetBuffer(n, IID_PPV_ARGS(&renderTargets[n]));
		DynamicRHI::Instance()->Device->CreateRenderTargetView(renderTargets[n].Get(), nullptr, rvtHandle);
		rvtHandle.Offset(1, rtvDescriptorSize);
	}


}
