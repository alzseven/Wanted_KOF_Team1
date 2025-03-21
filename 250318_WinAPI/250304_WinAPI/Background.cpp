#include "Background.h"
#include "Image.h"
#include "KOF_Iori.h"
#include "CommonFunction.h"
#include "KOF_TEST.h"
#include "MainGame.h"

void Background::Init()
{
	elapsedFrame = 0;
	currentFrameIndex = 0;
	camera = { WINSIZE_X/2, 0 };

	image = new Image();
	if (FAILED(image->Init(TEXT("Image/BackGround1.bmp"), WINSIZE_X*3, WINSIZE_Y*14, 1, 14, false, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd,TEXT("이미지 생성 실패"), TEXT("경고"), MB_OK);
	}

}

void Background::Release()
{

	if (maingame)
	{
		maingame->Release();
		delete maingame;
		maingame = nullptr;
	}

	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void Background::Update()
{
	elapsedFrame++;

	currentFrameIndex = elapsedFrame / 5;
	if (currentFrameIndex > 13)
	{
		elapsedFrame = 0;
	}

}

void Background::Render(HDC hdc)
{
	if (image)
	{
		image->Render(hdc, 0, 0, currentFrameIndex, camera.x, false);
	}
}

void Background::Camera(FPOINT player1Pos, FPOINT player2Pos)
{
	//FPOINT middlePoint = { (player2Pos.x - player1Pos.x) / 2, player1Pos.y }; // 둘 사이의 중간 지점
	//float ptMoveDistance = middlePoint.x - (WINSIZE_X / 2) ; // 중간 지점의 이동거리 = 화면의 이동량
	//float dist = abs(player1Pos.x - player2Pos.x);  // 두 캐릭터의 거리 // n 이상일 때만 camera 작동하도록 쓰일 용도 // abs() : 절대값

	// FSM -> MOVE 일떄 검사 후 카메라 이동 예정
	// 플레이어 두개 사이의 거리에 따라서 배경이 움직이는지 확인


			if (KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT) /*키입력 대신 player1의 왼이동 상태?*/ )
			{
				if (player1Pos.x < WINSIZE_X / 4)
				{
					if (!KeyManager::GetInstance()->IsStayKeyDown(VK_INSERT))
					{
						camera.x -= 1.5f;

						if (camera.x < 0) 
						{
							camera.x = 0;
						}
					}
					
				}
			}

			if (KeyManager::GetInstance()->IsStayKeyDown(VK_INSERT) /*player의 상태 */)
			{
				if (player2Pos.x < WINSIZE_X / 4)
				{
					camera.x -= 1.5f;

					if (camera.x < 0)
					{
						camera.x = 0;
					}

				}
			}

			if (KeyManager::GetInstance()->IsStayKeyDown(VK_SPACE))
			{
				if (player1Pos.x > WINSIZE_X / 2)
				{
					camera.x += 1.5f;

					if (camera.x > WINSIZE_X)
					{
						camera.x = WINSIZE_X;
					}
				}
			}

			if (KeyManager::GetInstance()->IsStayKeyDown(VK_DELETE))
			{
				if (player2Pos.x >  WINSIZE_X / 2)
				{
					if (!KeyManager::GetInstance()->IsStayKeyDown(VK_SPACE))
					{
						camera.x += 1.5f;

						if (camera.x > WINSIZE_X)
						{
							camera.x = WINSIZE_X;
						}
					}
				}
			}
}
