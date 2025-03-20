#include "KOF_Character.h"
#include "Image.h"

void KOF_Character::Init()
{
	health = 10;
	weakPunchDamage = 1;
	weakKickDamage = 1;
	strongPunchDamage = 3;
	strongKickDamage = 3;
	Pos = { 600, 300 };
	moveSpeed = 3;
	characterName = "Gato";
	hitRect = { 0,0,0,0 };
	attackRect = { 0,0,0,0 };
	elapsedFrame = 0;

	image = new Image[7];

	if (FAILED(image[0].Init(TEXT("Image/Ryo_Smove_Front"), 1097, 300, 6, 1, false, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[1].Init(TEXT("Image/"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[2].Init(TEXT("Image/"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[3].Init(TEXT("Image/"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[4].Init(TEXT("Image/"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[5].Init(TEXT("Image/"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("I파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[6].Init(TEXT("Image/"), 1097, 300, 6, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, TEXT("파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	currentFrameIndex = 0;
}

void KOF_Character::Release()
{
	delete[] image;
}

void KOF_Character::Update()
{
	// 이동
	
	if (KeyManager::GetInstance()->IsStayKeyDown(VK_SPACE))
	{
		elapsedFrame++;
		currentFrameIndex = elapsedFrame / 6;

		if (currentFrameIndex > 12)
		{
			elapsedFrame = 0;
		}

		
	}


	// 공격


}

void KOF_Character::Render(HDC hdc)
{
	// 
}

void KOF_Character::WeakPunch()
{

}

void KOF_Character::StrongPunch()
{

}

void KOF_Character::WeakKick()
{

}

void KOF_Character::StrongKick()
{
}

void KOF_Character::Guard(bool)
{
}
