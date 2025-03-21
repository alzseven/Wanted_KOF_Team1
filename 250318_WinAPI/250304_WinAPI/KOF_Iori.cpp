#include "KOF_Iori.h"
#include "Image.h"

void KOF_Iori::Init()
{
	pos = { WINSIZE_X/4, WINSIZE_Y-350 };
	moveSpeed = 5.0f;
	image = new Image();
	if (FAILED(image->Init(TEXT("Image/Ryo_move_Back.bmp"),780*2, 130*2, 6, 1, 
		true, RGB(255,0,255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	elapsedFrame = 0;
	currAnimaionFrame = 0;
}

void KOF_Iori::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void KOF_Iori::Update()
{
	if (KeyManager::GetInstance()->IsStayKeyDown(VK_SPACE))
	{	
		elapsedFrame++;
		pos.x += 3;
		currAnimaionFrame += elapsedFrame / 5;
		
		if (currAnimaionFrame > 5)
		{
			elapsedFrame = 0;
			currAnimaionFrame = 0;
			
		}
	}

	if (KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT))
	{
		elapsedFrame++;
		pos.x-= 3;
		currAnimaionFrame += elapsedFrame / 8;

		if (currAnimaionFrame > 8)
		{
			elapsedFrame = 0;
			currAnimaionFrame = 0;

		}
	}

}

void KOF_Iori::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y, currAnimaionFrame, false);
}

void KOF_Iori::Move()
{
	pos.x += moveSpeed;
}

KOF_Iori::KOF_Iori()
{
}

KOF_Iori::~KOF_Iori()
{
}
