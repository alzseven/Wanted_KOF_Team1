#include "KOF_TEST.h"
#include "Image.h"

void KOF_TEST::Init()
{
	pos = { 750.0f, 400.0f };
	moveSpeed = 5.0f;
	image = new Image();
	if (FAILED(image->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1,
		true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	elapsedFrame = 0;
	currAnimaionFrame = 0;
}

void KOF_TEST::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void KOF_TEST::Update()
{
	if (KeyManager::GetInstance()->IsStayKeyDown(VK_DELETE))
	{
		elapsedFrame++;
		pos.x+=3;
		currAnimaionFrame += elapsedFrame / 8;

		if (currAnimaionFrame > 8)
		{
			elapsedFrame = 0;
			currAnimaionFrame = 0;
		}
	}

	if (KeyManager::GetInstance()->IsStayKeyDown(VK_INSERT))
	{
		elapsedFrame++;
		pos.x-=3;
		currAnimaionFrame += elapsedFrame / 8;

		if (currAnimaionFrame > 8)
		{
			elapsedFrame = 0;
			currAnimaionFrame = 0;
		}
	}


}

void KOF_TEST::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, pos.x, pos.y, currAnimaionFrame, NULL, true);
}

void KOF_TEST::Move()
{
	pos.x += moveSpeed;
}

KOF_TEST::KOF_TEST()
{
}

KOF_TEST::~KOF_TEST()
{
}
