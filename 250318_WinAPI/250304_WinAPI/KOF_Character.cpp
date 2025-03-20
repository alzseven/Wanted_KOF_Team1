#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"

// 새로 만듦
void KOF_Character::WeakPunch()
{
	UpdateRect(combat->hitRect, { Pos.x + frame[State::WeakPunch].hitOffset.x, Pos.y + frame[State::WeakPunch].hitOffset.y });
	UpdateRect(combat->attackRect, { Pos.x + frame[State::WeakPunch].attackOffset.x, Pos.y + frame[State::WeakPunch].attackOffset.y });

	//combat->damage = weakKickDamage;

	if (currentActionIndex == State::WeakPunch) return;
	currentFrameIndex = 0;
	currentActionIndex = State::WeakPunch;
	elaspedFrame = 0.0f;
}

void KOF_Character::StrongPunch()
{
	UpdateRect(combat->hitRect, { Pos.x + frame[State::StrongPunch].hitOffset.x, Pos.y + frame[State::StrongPunch].hitOffset.y});		// 캐릭터마다 다름
	UpdateRect(combat->attackRect, { Pos.x + frame[State::StrongPunch].attackOffset.x, Pos.y + frame[State::StrongPunch].attackOffset.x });	// 캐릭터마다 다름
	
	//combat->damage = strongKickDamage;

	if (currentActionIndex == State::StrongPunch) return;
	currentFrameIndex = 0;
	currentActionIndex = State::StrongPunch;
	elaspedFrame = 0.0f;
}

void KOF_Character::WeakKick()
{
	UpdateRect(combat->hitRect, { Pos.x + frame[State::WeakKick].hitOffset.x, Pos.y + frame[State::WeakKick].hitOffset.y });
	UpdateRect(combat->attackRect, { Pos.x + frame[State::WeakKick].attackOffset.x, Pos.y + frame[State::WeakKick].attackOffset.y });

	//combat->damage = weakKickDamage;

	if (currentActionIndex == State::WeakKick) return;
	currentFrameIndex = 0;
	currentActionIndex = State::WeakKick;
	elaspedFrame = 0.0f;
}

void KOF_Character::StrongKick()
{
	UpdateRect(combat->hitRect, { Pos.x + frame[State::StrongKick].hitOffset.x, Pos.y + frame[State::StrongKick].hitOffset.y });
	UpdateRect(combat->attackRect, { Pos.x + frame[State::StrongKick].attackOffset.x, Pos.y + frame[State::StrongKick].attackOffset.y });

	//combat->damage = strongKickDamage;

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
	//combat->damage = 10;
	//

	// stateFrameInfo 초기화 - hit, attack offset 값 설정, 데미지 설정
	frame = new stateFrameInfo[7];
	frame[State::StrongKick].attackOffset = {85, 20};
	frame[State::StrongPunch].attackOffset = {85, 20};
	frame[State::WeakKick].attackOffset = {85, 80};
	frame[State::WeakPunch].attackOffset = {85, 20};

	frame[State::Idle].hitOffset = {50,50};
	frame[State::MovingBack].hitOffset = {50,50};
	frame[State::MovingFoward].hitOffset = {50,50};
	frame[State::StrongKick].hitOffset = {50,50};
	frame[State::StrongPunch].hitOffset = {50,50};
	frame[State::WeakKick].hitOffset = {50,50};
	frame[State::WeakPunch].hitOffset = {50,50};

	frame[State::StrongKick].damage = 10;
	frame[State::StrongPunch].damage = 10;
	frame[State::WeakKick].damage = 5;
	frame[State::WeakPunch].damage = 5;

	frame[State::Idle].frameSpeed = 10.;
	frame[State::MovingBack].frameSpeed = 15.;
	frame[State::MovingFoward].frameSpeed = 15.;
	frame[State::StrongKick].frameSpeed = 30.;
	frame[State::StrongPunch].frameSpeed = 40.;
	frame[State::WeakKick].frameSpeed = 30.;
	frame[State::WeakPunch].frameSpeed = 30.;
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
	if (frame)
	{
		delete [] frame;
		frame = nullptr;
	}

	if (combat)
	{
		delete combat;
		combat = nullptr;
	}

	if (image)
	{
		delete [] image;
		image = nullptr;
	}
}

void KOF_Character::Update()
{
	//float frameSpeed = 10.0f;

	elaspedFrame += frame[currentActionIndex].frameSpeed;


	if (elaspedFrame >= 100.0f)
	{
		currentFrameIndex++;

		elaspedFrame = 0.0f;
	}

	// 액션프레임
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


	if(currentActionIndex < 3)		// 액션을 취할 땐 움직이지 못하게 한다.
	{
		// D key : 앞이동
		if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))
		{
			currentFrameIndex = 0;
			//currentActionIndex = State::MovingFoward;
		}
		else if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
		{
			currentActionIndex = State::MovingFoward;
			if (currentFrameIndex >= 3)
			{
				Pos.x += 2.0f * (frame[currentActionIndex].frameSpeed / moveSpeed);
			}
			else
			{
				Pos.x += 1.0f * (frame[currentActionIndex].frameSpeed / moveSpeed);
			}
			if (currentFrameIndex >= 5)
			{
				currentFrameIndex = 0;
			}
			UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });

		}
		if (KeyManager::GetInstance()->IsOnceKeyUp(0x44))
		{
			currentActionIndex = State::Idle;
			currentFrameIndex = 0;
		}


		// A Key : 뒤로 이동
		if (KeyManager::GetInstance()->IsOnceKeyDown(0x41))
		{
			currentActionIndex = State::MovingBack;
			currentFrameIndex = 0;

		}
		else if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
		{
			currentActionIndex = State::MovingBack;
			Pos.x -= 2.0f * (frame[currentActionIndex].frameSpeed / moveSpeed);

			if (currentFrameIndex >= 5)
			{
				currentFrameIndex = 0;
			}
			UpdateRect(combat->hitRect, { Pos.x + 50, Pos.y + 50 });
		}
		if (KeyManager::GetInstance()->IsOnceKeyUp(0x41))
		{
			currentActionIndex = State::Idle;
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
