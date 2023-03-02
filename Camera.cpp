#include "Camera.h"

XMFLOAT3 Camera::GetPosition()
{
	return position;
}

XMFLOAT3 Camera::GetForward()
{
	return direction;
}

void Camera::SetPosition(const XMFLOAT3& pos)
{
	position = pos;
}

const XMFLOAT4X4& Camera::GetViewMatrix()
{
	UpdateViewMatrix();
	return viewMatrix;
}


const XMFLOAT4X4& Camera::GetProjectionMatrix()
{
	UpdateProjectMatrix();
	return projectionMatrix;
}

const XMFLOAT4X4& Camera::GetInverseProjectionViewMatrix()
{
	auto proj = XMLoadFloat4x4(&projectionMatrix);
	auto view = XMLoadFloat4x4(&viewMatrix);
	auto invProjView = XMMatrixInverse(nullptr, proj * view);
	XMStoreFloat4x4(&inverseProjectionView, invProjView);
	return inverseProjectionView;
}

const XMFLOAT4X4& Camera::GetViewProjectionMatrix()
{
	auto view = XMLoadFloat4x4(&viewMatrix);
	auto proj = XMLoadFloat4x4(&projectionMatrix);
	auto viewProj = view * proj;
	XMFLOAT4X4 viewProjT;
	XMStoreFloat4x4(&viewProjT, viewProj);
	return viewProjT;
}

const float& Camera::GetNearZ()
{
	return nearZ;
}

const float& Camera::GetFarZ()
{
	return farZ;
}

std::auto_ptr<Camera> Camera::BuildDefaultCamera(int width, int height)
{
	std::auto_ptr<Camera> camera = std::auto_ptr<Camera>();
	camera->nearZ = 0.1f;
	camera->farZ = 100;
	camera->fov = 45;
	camera->position = XMFLOAT3(0, 0, 0);
	camera->direction = XMFLOAT3(0, 0, 1);
	camera->width = width;
	camera->height = height;

	return camera;
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR forward = XMLoadFloat3(&direction);
	XMVECTOR pos = XMLoadFloat3(&position);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);

	//	auto rot = XMQuaternionRotationRollPitchYawFromVector(forward);

	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		forward,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)

	XMStoreFloat4x4(&viewMatrix, V);
}

void Camera::UpdateProjectMatrix()
{
	float aspectRatio = width / height;
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		fov/180.0f * XM_PI,
		aspectRatio,
		0.1f,
		1000.0f);
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P));
	XMStoreFloat4x4(&projectionMatrix, P);
}
