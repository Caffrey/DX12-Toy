#pragma once


#include "stdafx.h"

using namespace DirectX;


class Camera
{
	
protected:
	XMFLOAT4X4 viewMatrix;
	XMFLOAT4X4 projectionMatrix;
	XMFLOAT4X4 inverseProjectionView;
	XMFLOAT3 position;
	XMFLOAT3 direction;
	XMFLOAT4 rotation;
	
	float width;
	float height;
	float aspectRatio;

	float fov;
	float nearZ;
	float farZ;


public:
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetForward();
	
	void SetPosition(const XMFLOAT3& pos);
	const XMFLOAT4X4& GetViewMatrix();
	const XMFLOAT4X4& GetProjectionMatrix();
	const XMFLOAT4X4& GetInverseProjectionViewMatrix();
	const XMFLOAT4X4& GetViewProjectionMatrix();
	const float& GetNearZ();
	const float& GetFarZ();


public:

	Camera() {}
	~Camera() {}

	static std::auto_ptr<Camera> BuildDefaultCamera(int width, int height);
protected:

	void UpdateViewMatrix();
	void UpdateProjectMatrix();

};

