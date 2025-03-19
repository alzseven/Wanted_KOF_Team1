#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"

void KOF_Character::Init()
{
	health = 100;
	weakPunchDamage = 10;
	weakKickDamage = 15;
	strongPunchDamage = 20;
	strongKickDamage = 25;
	Pos = {30, 300};
	moveSpeed = 10.0f;
	characterName = "Mai";
	//hitRect;
	//attackRect;
	currentFrameIndex = 0;
	currentActionIndex = 0;
	elaspedFrame = 0.0f;
	
	/*	image = new Image();
	if (FAILED(image->Init(TEXT("Image/Mai_Shiranui/Mai.bmp"), 1455, 627, 15, 5,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
	*/

	image = new Image[5];

	if (FAILED(image[0].Init(TEXT("Image/Mai_Shiranui/Mai_Idle.bmp"), 1455, 114, 15, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Idle.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[1].Init(TEXT("Image/Mai_Shiranui/Mai_Back.bmp"), 552, 121, 6, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Back.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[2].Init(TEXT("Image/Mai_Shiranui/Mai_Foward.bmp"), 648, 124, 6, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Foward.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[3].Init(TEXT("Image/Mai_Shiranui/Mai_StrongPunch.bmp"), 773, 135, 6, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_StrongPunch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[4].Init(TEXT("Image/Mai_Shiranui/Mai_StrongKick.bmp"), 979, 133, 7, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_StrongKick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

}

void KOF_Character::Release()
{
	delete[] image;
}

void KOF_Character::Update()
{
	
	float frameSpeed = 10.0f;

	elaspedFrame += frameSpeed;


	if (elaspedFrame >= 100.0f)
	{
		currentFrameIndex++;

		elaspedFrame = 0.0f;
	}
	

	if (currentFrameIndex >= 15 && currentActionIndex == State::Idle)
	{
		currentFrameIndex = 0;
	}

	switch (currentActionIndex)
	{
	case State::StrongPunch:
		if (currentFrameIndex >= 6)
		{
			currentFrameIndex = 0;
			currentActionIndex = 0;
		}
		break;
	case State::StrongKick:
		if (currentFrameIndex >= 7)
		{
			currentFrameIndex = 0;
			currentActionIndex = 0;
		}
		break;
	}


	// D key : 앞이동
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))
	{
		currentFrameIndex = 0;
		currentActionIndex = State::MovingFoward;
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
	{
		Pos.x += 2.0f * (frameSpeed / moveSpeed);
		if (currentFrameIndex >= 6)
		{
			currentFrameIndex = 0;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(0x44))
	{
		currentFrameIndex = 0;
		currentActionIndex = State::Idle;
	}


	// A Key : 뒤로 이동
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x41))
	{
		currentFrameIndex = 0;
		currentActionIndex = State::MovingBack;
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
	{
		Pos.x -= 2.0f * (frameSpeed / moveSpeed);

		if (currentFrameIndex >= 6)
		{
			currentFrameIndex = 0;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(0x41))
	{
		currentFrameIndex = 0;
		currentActionIndex = State::Idle;
	}
	


	// J key : 강펀치
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x4A))
	{
		StrongPunch();
	}
	
	// K key : 강발
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x4B))
	{
		StrongKick();
	}
	


}

void KOF_Character::Render(HDC hdc)
{
	if (image)
		image[currentActionIndex].Render(hdc,Pos.x,Pos.y,currentFrameIndex,false);

}

void KOF_Character::WeakPunch()
{

}

void KOF_Character::StrongPunch()
{
	if (currentActionIndex == State::StrongPunch) return;
	currentFrameIndex = 0;
	currentActionIndex = State::StrongPunch;
	elaspedFrame = 0.0f;
}


void KOF_Character::WeakKick()
{

}

void KOF_Character::StrongKick()
{
	if (currentActionIndex == State::StrongKick) return;
	currentFrameIndex = 0;
	currentActionIndex = State::StrongKick;
	elaspedFrame = 0.0f;
}

bool KOF_Character::Guard(bool)
{
	return true;
}

