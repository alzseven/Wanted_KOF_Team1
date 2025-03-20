#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"

// 새로 만듦
void KOF_Character::WeakPunch()
{
	//UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });		
	//UpdateRect(combat->attackRect, { Pos.x + 85, Pos.y + 20 });	

	combat->damage = weakKickDamage;

	if (currentActionIndex == State::WeakPunch) return;
	currentFrameIndex = 0;
	currentActionIndex = State::WeakPunch;
	elaspedFrame = 0.0f;
}

void KOF_Character::StrongPunch()
{
	UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });		// 캐릭터마다 다름
	UpdateRect(combat->attackRect, { Pos.x + 85, Pos.y + 20 });	// 캐릭터마다 다름
	
	combat->damage = strongKickDamage;

	if (currentActionIndex == State::StrongPunch) return;
	currentFrameIndex = 0;
	currentActionIndex = State::StrongPunch;
	elaspedFrame = 0.0f;
}

void KOF_Character::WeakKick()
{
	UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });
	UpdateRect(combat->attackRect, { Pos.x + 85, Pos.y + 80 });

	combat->damage = weakKickDamage;

	if (currentActionIndex == State::WeakKick) return;
	currentFrameIndex = 0;
	currentActionIndex = State::WeakKick;
	elaspedFrame = 0.0f;
}

void KOF_Character::StrongKick()
{
	UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });
	UpdateRect(combat->attackRect, { Pos.x + 85, Pos.y + 20 });

	combat->damage = strongKickDamage;

	if (currentActionIndex == State::StrongKick) return;
	currentFrameIndex = 0;
	currentActionIndex = State::StrongKick;
	elaspedFrame = 0.0f;
}

bool KOF_Character::Guard(bool isSuccess)
{
	return false;
}

void KOF_Character::Init()		// 나
{
	health = 100;
	weakPunchDamage = 5;
	weakKickDamage = 5;
	strongPunchDamage = 10;
	strongKickDamage = 10;
	Pos = {30.0f, 300.0f};
	moveSpeed = 10.0f;
	characterName = "King";
	
	//image = new Image;
	//if (FAILED(image->Init(TEXT("Image/kingStrongKick.bmp"), 1000, 110, 10, 1,
	//	true, RGB(103, 167, 141))))
	//{
	//	MessageBox(g_hWnd, TEXT("Image/kingStrongKick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	//}

	// combatInfo 초기화-rect 크기 설정
	combat = new combatInfo;

	combat->hitRect = { 0, 0, 30, 110 };
	combat->attackRect = { 0,0,30, 20 };
	combat->damage = 10;
	//


	currentFrameIndex = 0;
	currentActionIndex = 0;
	elaspedFrame = 0.0f;

	image = new Image[7];

	if (FAILED(image[0].Init(TEXT("Image/kingDefault.bmp"), 700, 110, 7, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingDefault.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[1].Init(TEXT("Image/kingForward.bmp"), 500, 110, 5, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingForward.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[2].Init(TEXT("Image/kingForward.bmp"), 500, 110, 5, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingForward.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[3].Init(TEXT("Image/kingStrongPunch.bmp"), 600, 130, 6, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingStrongPunch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[4].Init(TEXT("Image/kingStrongKick.bmp"), 1000, 110, 10, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingStrongKick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	// weak
	if (FAILED(image[5].Init(TEXT("Image/kingWeakPunch.bmp"), 500, 110, 5, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingWeakPunch.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}

	if (FAILED(image[6].Init(TEXT("Image/kingWeakKick.bmp"), 500, 110, 5, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingWeakKick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	}
}

void KOF_Character::Release()		// 나
{
	if (image)
	{
		delete [] image;
		image = nullptr;
	}

	if (combat)
	{
		delete combat;
		combat = nullptr;
	}
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

	switch (currentActionIndex)
	{
	case State::Idle:
		if (currentFrameIndex >= 5)
		{
			currentFrameIndex = 0;
		}
		break;
	case State::StrongPunch:
		if (currentFrameIndex >= 6)
		{
			currentFrameIndex = 0;
			currentActionIndex = State::Idle;
		}
		break;
	case State::StrongKick:
		if (currentFrameIndex >= 10)
		{
			currentFrameIndex = 0;
			currentActionIndex = State::Idle;
		}
		break;
	case State::WeakPunch:
		if (currentFrameIndex >= 5)
		{
			currentFrameIndex = 0;
			currentActionIndex = State::Idle;
		}
		break;
	case State::WeakKick:
		if (currentFrameIndex >= 5)
		{
			currentFrameIndex = 0;
			currentActionIndex = State::Idle;
		}
		break;
	}


	// D key : 앞이동
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))
	{
		currentFrameIndex = 0;
		currentActionIndex = State::MovingFoward;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
	{
		Pos.x += 2.0f * (frameSpeed / moveSpeed);
		if (currentFrameIndex >= 5)
		{
			currentFrameIndex = 0;
		}
		UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });

	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(0x44))
	{
		currentActionIndex = State::Idle;
		if (currentFrameIndex >= 5)
		{
			currentFrameIndex = 0;
		}
	}


	// A Key : 뒤로 이동
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x41))
	{
		currentFrameIndex = 0;
		currentActionIndex = State::MovingBack;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
	{
		Pos.x -= 2.0f * (frameSpeed / moveSpeed);

		if (currentFrameIndex >= 5)
		{
			currentFrameIndex = 0;
		}
		UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(0x41))
	{
		currentActionIndex = State::Idle;
		if (currentFrameIndex >= 5)
		{
			currentFrameIndex = 0;
		}
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

	// weak
	// U key : 약펀치
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x55))
	{
		UpdateRect(combat->attackRect, { Pos.x + 85, Pos.y + 20 });
		WeakPunch();
	}
	// I key : 강펀치
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x49))
	{
		WeakKick();
	}
}

void KOF_Character::Render(HDC hdc)
{
	// test
	RenderRect(hdc, combat->hitRect);
	RenderRect(hdc, combat->attackRect);
	// test
	//RenderRectAtCenter(hdc, Pos.x, Pos.y, 100, 110);
	if (image)
		image[currentActionIndex].Render(hdc, Pos.x, Pos.y, currentFrameIndex, false);

}
