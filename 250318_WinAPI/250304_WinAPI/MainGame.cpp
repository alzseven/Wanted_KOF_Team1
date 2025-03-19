#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "GameManager.h"

/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/

void MainGame::Init()
{
	gameManager = new GameManager();
	gameManager->Init();
}

void MainGame::Release()
{
	gameManager->Release();
	delete gameManager;
}

void MainGame::Update()
{
	gameManager->Update();
	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	gameManager->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 10, NULL);

		break;
	case WM_TIMER:
		this->Update();
		break;
	// case WM_KEYDOWN:
	// 	switch (wParam)
	// 	{
	// 	case 'a': case 'A':
	// 		break;
	// 	case 'd': case 'D':
	// 		break;
	// 	}
	// 	break;
	// case WM_LBUTTONDOWN:
	// 	mousePosX = LOWORD(lParam);
	// 	mousePosY = HIWORD(lParam);
	//
	// 	break;
	// case WM_LBUTTONUP:
	// 	break;
	// case WM_MOUSEMOVE:
	// 	mousePosX = LOWORD(lParam);
	// 	mousePosY = HIWORD(lParam);
	//
	// 	mousePos.x = LOWORD(lParam);
	// 	mousePos.y = HIWORD(lParam);
	// 	break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		this->Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
