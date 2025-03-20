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
	UI* GameUI_Hostile;
	KOF_Character* myCharacter;		//본인의 캐릭터
	KOF_Character* hostileCharacter;	//상대의 캐릭터

public:
	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();	
	void Update();	
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

