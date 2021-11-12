#pragma once
#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
private:
    static Camera* mCamera;
    Camera(int width, int height);
    int             mWidth,
        mHeight;

    D3DXVECTOR3     mPosition;
public:

    //center of camera
    void SetPosition(float x, float y);
    void SetPosition(D3DXVECTOR3 pos);

    int GetWidth();
    int GetHeight();

    D3DXVECTOR3 Transform(float x, float y);
    D3DXVECTOR3 Transform(D3DXVECTOR2 pos);
    D3DXVECTOR3 Transform(D3DXVECTOR3 pos);

    static Camera* GetInstance(int width, int height);

    D3DXVECTOR3 GetPosition();
    RECT GetBound();

    ~Camera();

};
