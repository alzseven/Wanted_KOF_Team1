#pragma once
#include "GameObject.h"

class MainGame;
class KOF_TEST;
class KOF_Iori;
class Image;
class Background : public GameObject
{
private:
	int elapsedFrame;
	int currentFrameIndex;
	FPOINT camera; // 이미지 좌표
	FPOINT middlePos; // 두 캐릭터의 중간지점 좌표
	float scrMoveDistance; // 중간 지점의 이동거리 = 화면의 이동량
	float dist; // 두 캐릭터의 거리 // n 이상일 때만 camera 작동하도록 쓰일 용도


	Image* image;
	MainGame* maingame;

public:
	

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Camera(FPOINT player1Pos, FPOINT player2Pos);

	FPOINT GetCamera() { return camera; }

};

