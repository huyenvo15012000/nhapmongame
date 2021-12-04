#ifndef CAMERA_H
#define CAMERA_H

#include <DirectXMath.h>
#include "MainObject.h"

class Camera
{
public:
	//Constructors and Destructor
	Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	//Game Functions
	void Update();
	void Follow(CMainObject* following);
	void Unfollow();
	bool IsFollowing() const;
	void SetTransform(LPDIRECT3DDEVICE9 device) const;
	void FlipY(float& y) {
		y = 496 - y;
	}
	D3DVECTOR GetPosition();

private:
	float angle;
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;

	CMainObject* following;

	int width;
	int height;
	D3DVECTOR position;
};

#endif /* CAMERA_H */
