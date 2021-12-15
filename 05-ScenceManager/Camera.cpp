#include "Camera.h"
#include "MainObject.h"
#include "Utils.h"

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->scaleFactors = scaleFactors;
	scenes_height.push_back(344);
	scenes_height.push_back(496);
	curent_scene_height = scenes_height.at(1);
	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	float camX = 0, camY = 0;
	if (this->following)
	{
		this->following->GetPosition(camX, camY);
	}
	FlipY(camY);
	if (camX < width/2)
		camX = width / 2;
	if (camY < height/2)
		camY = height/2;
	if (camX > 1232-170)
		camX = 1232-170;
	if (camY > curent_scene_height -height/2)
		camY = curent_scene_height - height / 2;
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




