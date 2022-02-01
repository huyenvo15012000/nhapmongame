#ifndef CAMERA_H
#define CAMERA_H

#pragma warning

#include <DirectXMath.h>
#include "MainObject.h"

class Camera
{
	vector<int> scenes_height;
	vector<int> scenes_width;
	int curent_scene_height;
	int curent_scene_width;
	int scene_id;
	int test;
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
		y = curent_scene_height - y;
	}
	void SetSceneHeight(int i) { 
		this->curent_scene_height = scenes_height.at(i - 1);
		this->curent_scene_width = scenes_width.at(i - 1);
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
