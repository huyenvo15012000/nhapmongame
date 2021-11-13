#include "Camera.h"
#include "Game.h"

Camera* Camera::mCamera = NULL;

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{
    mWidth = width;
    mHeight = height;
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
        float cameraX = this->following->GetX();
        float cameraY = this->following->GetY();
        this->viewMatrix = D3DXMATRIX(scaleFactors.x * cos(angle), scaleFactors.x * sin(angle), 0, 0,
            -scaleFactors.y * sin(angle), scaleFactors.y * cos(angle), 0, 0,
            0, 0, scaleFactors.z, 0,
            -cameraX * scaleFactors.x * cos(angle) + cameraY * scaleFactors.y * sin(angle), -cameraX * scaleFactors.y * sin(angle) - cameraY * scaleFactors.y * cos(angle), 0, 1
        );
}

void Camera::Follow(CMainObject* main)
{
    this->following = main;
}

Camera* Camera::GetInstance(int width, int height)
{
    if (mCamera == NULL) {
        mCamera = new Camera(width, height);
    }
    return mCamera;
}

int Camera::GetWidth()
{
    return mWidth;
}

int Camera::GetHeight()
{
    return mHeight;
}
void Camera::setTransform(CGame* gDevice) const
{
    gDevice->GetDirect3DDevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
    gDevice->GetDirect3DDevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
    gDevice->GetDirect3DDevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}