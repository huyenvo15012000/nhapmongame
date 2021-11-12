#include "Camera.h"
Camera* Camera::mCamera = NULL;

Camera::Camera(int width, int height)
{
    mWidth = width;
    mHeight = height;

    mPosition = D3DXVECTOR3(0, 0, 0);


}


Camera::~Camera()
{

}

void Camera::SetPosition(float x, float y)
{
    SetPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
    mPosition = pos;
}

D3DXVECTOR3 Camera::GetPosition()
{
    return mPosition;
}

RECT Camera::GetBound()
{
    RECT bound;

    bound.left = mPosition.x - mWidth / 2;
    bound.right = bound.left + mWidth;;
    bound.top = mPosition.y + mHeight / 2;
    bound.bottom = bound.top - mHeight;

    return bound;
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
D3DXVECTOR3 Camera::Transform(float x, float y)
{
    D3DXMATRIX matrix;
    D3DXMatrixIdentity(&matrix);
    matrix._22 = -1;
    matrix._41 = -mPosition.x + this->mWidth / 2;
    matrix._42 = mPosition.y + this->mHeight / 2;
    D3DXVECTOR3 Pos3(x, y, 1);
    D3DXVECTOR4 Pos4;
    D3DXVec3Transform(&Pos4, &Pos3, &matrix);
    D3DXVECTOR3 result = D3DXVECTOR3((int)Pos4.x, (int)Pos4.y, 0.0);
    return result;
}
D3DXVECTOR3 Camera::Transform(D3DXVECTOR2 pos)
{
    return Transform(pos.x, pos.y);
}
D3DXVECTOR3 Camera::Transform(D3DXVECTOR3 pos)
{
    return Transform(pos.x, pos.y);
}