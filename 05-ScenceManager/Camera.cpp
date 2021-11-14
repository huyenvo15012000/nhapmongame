#include "Camera.h"
#include "Mario.h"

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->scaleFactors = scaleFactors;

	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	if (this->following)
	{
		this->following->GetPosition(this->position.x, this->position.y);
	}

	this->viewMatrix = D3DXMATRIX(
		scaleFactors.x * cos(angle), scaleFactors.x * sin(angle), 0, 0,
		-scaleFactors.y * sin(angle), scaleFactors.y * cos(angle), 0, 0,
		0, 0, scaleFactors.z, 0,
		-this->position.x * scaleFactors.x * cos(angle) + this->position.y * scaleFactors.y * sin(angle), -this->position.x * scaleFactors.y * sin(angle) - this->position.y * scaleFactors.y * cos(angle), 0, 1
	);
}

void Camera::Follow(CMario* following)
{
	this->following = following;
}

void Camera::Unfollow()
{
	this->following = nullptr;
}

bool Camera::IsFollowing() const
{
	return this->following != nullptr;
}

void Camera::SetTransform(LPDIRECT3DDEVICE9 gDevice) const
{
	gDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	gDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	gDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}

D3DVECTOR Camera::GetPosition() {
	return this->position;
}




