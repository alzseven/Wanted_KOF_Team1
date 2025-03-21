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
		MessageBox(g_hWnd,TEXT("�̹��� ���� ����"), TEXT("���"), MB_OK);
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
	//FPOINT middlePoint = { (player2Pos.x - player1Pos.x) / 2, player1Pos.y }; // �� ������ �߰� ����
	//float ptMoveDistance = middlePoint.x - (WINSIZE_X / 2) ; // �߰� ������ �̵��Ÿ� = ȭ���� �̵���
	//float dist = abs(player1Pos.x - player2Pos.x);  // �� ĳ������ �Ÿ� // n �̻��� ���� camera �۵��ϵ��� ���� �뵵 // abs() : ���밪

	// FSM -> MOVE �ϋ� �˻� �� ī�޶� �̵� ����
	// �÷��̾� �ΰ� ������ �Ÿ��� ���� ����� �����̴��� Ȯ��


			if (KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT) /*Ű�Է� ��� player1�� ���̵� ����?*/ )
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

			if (KeyManager::GetInstance()->IsStayKeyDown(VK_INSERT) /*player�� ���� */)
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
