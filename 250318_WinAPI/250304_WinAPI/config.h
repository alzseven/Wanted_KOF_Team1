// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>

#include "KeyManager.h"

enum class EAttackHeightType;
using namespace std;

/*
	컴파일러에서 해당 코드를 뒤에 정의된 코드로 변경한다. 
*/
#define WINSIZE_X	640
#define WINSIZE_Y	480
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
	EAttackHeightType attackHeightType;
	RECT attackRect;
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

enum class EKOF_CharacterAction{
	IDLE,
	MOVE_FORWARD,
	MOVE_BACK,
	ATTACK_WEAK_PUNCH,
	ATTACK_WEAK_KICK,
	ATTACK_STRONG_PUNCH,
	ATTACK_STRONG_KICK,
	GUARD_STAND,
	GUARD_SIT,
	HIT_STUN,
	COUNT_MAX,
};

struct StateFrameInfo
{
	EKOF_CharacterAction action;
	SpriteSheetInfo spriteSheet;
	RECT rectHit;
	RECT rectAttack;
	int damage;
	float frameSpeed;
	FPOINT rectHitOffset;
	FPOINT rectAttackOffset;
};

//TODO: maxHealth;
//TODO: moveSpeed;
struct CharacterInfo
{
	int maxHealth;
	float moveSpeed;
	// int weakPunchDamage;
	// int weakKickDamage;
	// int strongPunchDamage;
	// int strongKickDamage;
	string characterName;
	// SpriteSheetInfo* spriteSheet;
	StateFrameInfo* frameInfo;
};

const int GUARD_DETECTION_DISTANCE = 150;
const float FRAME_TICK = 1000 / 30.f;
const int TIMER_TICK = 10;