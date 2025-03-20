#pragma once
#include "GameObject.h"

class Image;
class KOF_TEST : public GameObject
{
private:
	FPOINT pos;
	float moveSpeed;
	Image* image;
	int elapsedFrame;
	int currAnimaionFrame;	// 0 ~ 8

public:
	FPOINT GetPos() { return pos; }

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();

	KOF_TEST();
	~KOF_TEST();
};