#pragma once
#include "GameObject.h"

class UI;
class Image;
class KOF_Iori;
class KOF_Character;
//class KOF_Athena_Asamiya;
class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	FPOINT mousePos;
	wchar_t szText[128];

	Image* backBuffer;
	Image* backGround;
	KOF_Iori* iori;
	//KOF_Athena_Asamiya* Asamiya;
	UI* GameUI;
	KOF_Character* myCharacter;		//����� ĳ����

public:
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();	
	void Update();	
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

