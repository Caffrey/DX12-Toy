#pragma once

#include "stdafx.h"


using namespace DirectX;

class Transform
{
protected:
	XMFLOAT4X4 localToWorld;
	XMFLOAT4X4 worldToLocal;
	
	XMFLOAT3 localPosition;
	XMFLOAT3 localEuler;
	XMFLOAT4 localRotation;
	XMFLOAT3 localScale;

	XMFLOAT3 forward;


public:


	Transform();
		
protected:

	void UpdateMatrix();
};

