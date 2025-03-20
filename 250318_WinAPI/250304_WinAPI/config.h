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

struct combatInfo
{
	RECT hitRect;
	RECT attackRect;
};

struct stateFrameInfo
{
	FPOINT hitOffset = { 0,0 };
	FPOINT attackOffset = { 0,0 };
	int damage = 0;		// ���ݸ��� ������ �ٸ�
	float frameSpeed = 10.;
};
