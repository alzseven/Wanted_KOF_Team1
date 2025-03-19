#include "Background.h"

void Background::Init()
{
	elapsedFrame = 0;
	currentFrameIndex = 0;

	image = new Image();
	if (FAILED(image->Init(TEXT("Image/BackGround1.bmp"), WINSIZE_X, WINSIZE_Y * 14, 1, 14, false, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd,TEXT("이미지 생성 실패"), TEXT("경고"), MB_OK);
	}
}

void Background::Release()
{
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
		image->Render(hdc, 0, 0, currentFrameIndex, false);
	}
}
