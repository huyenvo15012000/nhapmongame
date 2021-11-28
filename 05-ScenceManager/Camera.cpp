#include "Camera.h"
#include "MainObject.h"

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
	float camX, camY = 0;
	if (this->following)
	{
		this->following->GetRealPosition(camX, camY);
	}
	//if (camX < 170)
	//	camX = 170;
	//if (camY < 120)
	//	camY = 120;
	//if (camX > 1232-170)
	//	camX = 1232-170;
	//if (camY > 496 -120)
	//	camY = 496 -120;
	this->viewMatrix = D3DXMATRIX(
		scaleFactors.x * cos(angle), scaleFactors.x * sin(angle), 0, 0,
		-scaleFactors.y * sin(angle), scaleFactors.y * cos(angle), 0, 0,
		0, 0, scaleFactors.z, 0,
		-camX * scaleFactors.x * cos(angle) + camY * scaleFactors.y * sin(angle), -camX * scaleFactors.y * sin(angle) - camY * scaleFactors.y * cos(angle), 0, 1
	);
}

void Camera::Follow(CMainObject* following)
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




