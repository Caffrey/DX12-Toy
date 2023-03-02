#include "DynamicRHI.h"


DynamicRHI DynamicRHI::m_Instance;
void DynamicRHI::InitRHI(ComPtr<IDXGIAdapter1> inAdapater, ComPtr<IDXGIFactory4> inFactory, int Width, int Height)
{

	ScreenWidth = Width;
	ScreenHeight = Height;
	Adapter = inAdapater;
	factory = inFactory;

	AspectRatio = static_cast<float>(Width) / static_cast<float>(Height);

	D3D12CreateDevice(
		Adapter.Get(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&Device)
	);
		
		
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&CommandQueue));
}
