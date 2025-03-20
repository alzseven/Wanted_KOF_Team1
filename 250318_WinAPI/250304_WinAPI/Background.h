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
	FPOINT camera; // �̹��� ��ǥ
	FPOINT middlePos; // �� ĳ������ �߰����� ��ǥ
	float scrMoveDistance; // �߰� ������ �̵��Ÿ� = ȭ���� �̵���
	float dist; // �� ĳ������ �Ÿ� // n �̻��� ���� camera �۵��ϵ��� ���� �뵵


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

