// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>

#include "KeyManager.h"

using namespace std;

/*
	�����Ϸ����� �ش� �ڵ带 �ڿ� ���ǵ� �ڵ�� �����Ѵ�. 
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
	extern Ű���� : ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִ� ���
	����� �˸��� Ű����.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

/* ���� ������ ��� ����ü */
typedef struct combatInfo
{
	RECT hitRect;
	int damage = 0;

} COMBATINFO;

/* UI ������ ��� ����ü */
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