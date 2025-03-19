// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>

#include "KeyManager.h"

using namespace std;

/*
	컴파일러에서 해당 코드를 뒤에 정의된 코드로 변경한다. 
*/
#define WINSIZE_X	1080
#define WINSIZE_Y	500
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)
#define RESET 0

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;



/*
	extern 키워드 : 변수나 함수가 다른 파일에 정의되어 있다 라는
	사실을 알리는 키워드.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

/* 전투 정보를 담는 구조체 */
typedef struct combatInfo
{
	RECT hitRect;
	int damage = 0;

} COMBATINFO;

/* UI 정보를 담는 구조체 */
typedef struct uiInfo
{
	string name;
	int health;
} UIINFO;


struct SpriteSheetInfo
{
	string sheetName;
	const wchar_t* filename;
	int width;
	int height;
	int maxFrameX;
	int maxFrameY;
	bool isTransparent;
	COLORREF transColor;
};

//TODO: maxHealth;
//TODO: moveSpeed;
struct CharacterInfo
{
	int health;
	int weakPunchDamage;
	int weakKickDamage;
	int strongPunchDamage;
	int strongKickDamage;
	string characterName;
	SpriteSheetInfo* spriteSheet;
};