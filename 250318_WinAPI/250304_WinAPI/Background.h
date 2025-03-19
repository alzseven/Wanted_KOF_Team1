#pragma once
#include "Image.h"
#include "GameObject.h"

class Background : public GameObject
{
private:
	int elapsedFrame;
	int currentFrameIndex;
	Image* image;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

