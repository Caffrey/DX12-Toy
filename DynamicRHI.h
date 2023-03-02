#pragma once

#include "stdafx.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class DynamicRHI
{
public:
	static DynamicRHI* Instance()
	{
		return &m_Instance;
	}
	void InitRHI(ComPtr<IDXGIAdapter1> inAdapater, ComPtr<IDXGIFactory4> inFactory, int Width, int Height);

private: 
	static DynamicRHI m_Instance;
	DynamicRHI() {};
	~DynamicRHI() {};

public:
	

	ComPtr< ID3D12GraphicsCommandList> commandlist;
	ComPtr<ID3D12Device> Device;
	ComPtr<ID3D12CommandQueue> CommandQueue;



	ComPtr<IDXGIAdapter1> Adapter;
	ComPtr<IDXGIFactory4> factory;

	float AspectRatio;

	int ScreenWidth;
	int ScreenHeight;


};

