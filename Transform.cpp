#include "Transform.h"

Transform::Transform()
{
	localPosition = XMFLOAT3(0, 0, 0);
	localRotation = XMFLOAT4(0, 0, 0,1);
	localEuler = XMFLOAT3(0, 0, 0);
	localScale = XMFLOAT3(0, 0, 0);


	forward = XMFLOAT3(0, 0, 1);

	

	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	XMFLOAT3 zero(0, 0, 0);
	XMVECTOR origin = XMLoadFloat3(&zero);

	XMVECTOR position = XMLoadFloat3(&localPosition);
	XMVECTOR euler = XMLoadFloat3(&localEuler);
	XMVECTOR scale = XMLoadFloat3(&localScale);

	XMVECTOR rotation = XMQuaternionRotationRollPitchYawFromVector(euler);
	 
	XMMATRIX localToWorld = XMMatrixAffineTransformation(scale, origin, rotation, position);
	XMMATRIX WorldToLocal = XMMatrixInverse( nullptr,localToWorld);
}
