#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"

void KOF_Character::WeakPunch(RECT& hitRect, RECT& attackRect, int& damage)		// 나
{
	// Rect를 반환
	// 데미지도 줘야됨
	UpdateRect(this->hitRect, {Pos.x+50, Pos.y+50});		// 캐릭터마다 다름
	UpdateRect(this->attackRect, { Pos.x +85, Pos.y+20});	// 캐릭터마다 다름

	hitRect = this->hitRect;
	attackRect = this->attackRect;
	damage = weakKickDamage;

	if (currentActionIndex == State::WeakPunch) return;
	currentFrameIndex = 0;
	currentActionIndex = State::WeakPunch;
	elaspedFrame = 0.0f;

}

void KOF_Character::StrongPunch(RECT& hitRect, RECT& attackRect, int& damage)
{
	UpdateRect(this->hitRect, { Pos.x + 50, Pos.y + 50 });		// 캐릭터마다 다름
	UpdateRect(this->attackRect, { Pos.x + 85, Pos.y + 20 });	// 캐릭터마다 다름

	hitRect = this->hitRect;
	attackRect = this->attackRect;
	damage = strongKickDamage;


	if (currentActionIndex == State::StrongPunch) return;
	currentFrameIndex = 0;
	currentActionIndex = State::StrongPunch;
	elaspedFrame = 0.0f;

}

void KOF_Character::WeakKick(RECT &hitRect, RECT &attackRect, int &damage)		// 나
{
	// 게임 매니저에서 호출됨, 캐릭터의 피격, 공격 rect 반환, 데미지 값도 반환...
	// Rect
	UpdateRect(this->hitRect, { Pos.x+50, Pos.y+50 });
	UpdateRect(this->attackRect, { Pos.x+85, Pos.y + 80 });

	hitRect = this->hitRect;
	attackRect = this->attackRect;
	damage = weakKickDamage;

	if (currentActionIndex == State::WeakKick) return;
	currentFrameIndex = 0;
	currentActionIndex = State::WeakKick;
	elaspedFrame = 0.0f;
}

void KOF_Character::StrongKick(RECT& hitRect, RECT& attackRect, int& damage)
{
	UpdateRect(this->hitRect, { Pos.x + 50, Pos.y + 50 });
	UpdateRect(this->attackRect, { Pos.x + 85, Pos.y + 20 });
	
	hitRect = this->hitRect;
	attackRect = this->attackRect;
	damage = strongKickDamage;

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
	hitRect =GetRect(Pos.x, Pos.y, 30, 110);    // 피격범위 - 나중에 UpdateRect로 위치에 맞게 업데이트
	attackRect = GetRect(Pos.x, Pos.y, 30, 20); // 공격범위 - 마찬가지
	
	//image = new Image;
	//if (FAILED(image->Init(TEXT("Image/kingStrongKick.bmp"), 1000, 110, 10, 1,
	//	true, RGB(103, 167, 141))))
	//{
	//	MessageBox(g_hWnd, TEXT("Image/kingStrongKick.bmp 파일 로드에 실패"), TEXT("경고"), MB_OK);
	//}

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
		StrongPunch(hitRect, attackRect, strongPunchDamage);
	}

	// K key : 강발
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x4B))
	{
		StrongKick(hitRect, attackRect, strongPunchDamage);
	}

	// weak
	// U key : 약펀치
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x55))
	{
		WeakPunch(hitRect, attackRect, weakPunchDamage);		// 실제론 게임매니저에서 받아야 하는 거
	}
	// I key : 강펀치
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x49))
	{
		WeakKick(hitRect, attackRect, weakKickDamage);
	}
}

void KOF_Character::Render(HDC hdc)
{
	// test
	RenderRect(hdc, hitRect);
	RenderRect(hdc, attackRect);
	// test
	//RenderRectAtCenter(hdc, Pos.x, Pos.y, 100, 110);
	if (image)
		image[currentActionIndex].Render(hdc, Pos.x, Pos.y, currentFrameIndex, false);

}
