#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
//#include "KOF_Iori.h"
#include "KOF_Athena_Asamiya.h"

/*
	실습1. 이오리 집에 보내기
	실습2. 배경 바꾸기 (킹오파 애니메이션 배경)
*/

void MainGame::Init()
{
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp 생성 실패"), TEXT("경고"), MB_OK);
	}

	/*iori = new KOF_Iori();
	iori->Init();*/

	Asamiya = new KOF_Athena_Asamiya();
	Asamiya->Init();
}

void MainGame::Release()
{
	/*if (iori)
	{
		iori->Release();
		delete iori;
		iori = nullptr;
	}*/

	if (Asamiya)
	{
		Asamiya->Release();
		delete Asamiya;
		Asamiya = nullptr;
	}

	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}
}

void MainGame::Update()
{
	/*if (iori)
		iori->Update();*/

	if (Asamiya)
		Asamiya->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);
	//iori->Render(hBackBufferDC);
	Asamiya->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

	// 백버퍼에 있는 내용을 메인 hdc에 복사
	backBuffer->Render(hdc);
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
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			Asamiya->Move(-(Asamiya->getMoveSpeed()), 0);
			break;
		case VK_RIGHT:
			Asamiya->Move(Asamiya->getMoveSpeed(), 0);
			break;
		case VK_UP:
			Asamiya->Move(0, Asamiya->getJump());
			break;
		case 'a': case 'A':
			Asamiya->WeakPunch();
			break;
		case 's': case 'S':
			Asamiya->StrongPunch();
			break;
		case 'z': case 'Z':
			Asamiya->WeakKick();
			break;
		case 'x': case 'X':
			Asamiya->StrongKick();
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);
		break;
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
