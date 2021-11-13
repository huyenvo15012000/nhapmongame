#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <DirectXMath.h>

#include <d3dx9.h>
#include <d3d9.h>
#include "MainObject.h"
#include "Game.h"


class Camera
{
private:
    static Camera* mCamera;
    Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
    Camera(int width, int height);
    int mWidth, mHeight;

    D3DXVECTOR3     mPosition;
    float angle;
    DirectX::XMFLOAT3 scaleFactors;
    D3DXMATRIX orthographicMatrix;
    D3DXMATRIX identityMatrix;
    D3DXMATRIX viewMatrix;

    CMainObject* following;

public:

    //center of camera
    /*void SetPosition(float x, float y);
    void SetPosition(D3DXVECTOR3 pos);

    

    D3DXVECTOR3 Transform(float x, float y);
    D3DXVECTOR3 Transform(D3DXVECTOR2 pos);
    D3DXVECTOR3 Transform(D3DXVECTOR3 pos);

    

    D3DXVECTOR3 GetPosition();
    RECT GetBound();*/
    static Camera* GetInstance(int width, int height);
    void Update();
    void Follow(CMainObject* following);
    void setTransform(CGame* gDevice) const;
    int GetWidth();
    int GetHeight();
    ~Camera();

};
#endif // !1


