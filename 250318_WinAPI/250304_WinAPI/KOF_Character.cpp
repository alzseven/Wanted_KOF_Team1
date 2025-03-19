#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"
#include "Image.h"

void KOF_Character::Init(bool isMovable)
{
	health = 100;
	weakPunchDamage = 10;
	weakKickDamage = 15;
	strongPunchDamage = 20;
	strongKickDamage = 25;
	pos = {30, 300};
	moveSpeed = 10.0f;

	characterName = "None";

	currentFrameIndex = 0;
	currentActionState = 0;
	elaspedFrame = 0.0f;
    currentCombatInfo.damage = weakPunchDamage;
    currentCombatInfo.hitRect = hitRect;
    hitRect = RECT{ (int)(pos.x + 100), (int)(pos.y),  (int)(pos.x + 100) + 20 , (int)pos.y + 100 };
	
    isWeakPunching = true;

    this->isMoveable = isMoveable;

	elaspedFrame = 0;
    currAnimaionFrame = 0;

}

void KOF_Character::Init(const CharacterInfo info, bool isMoveable, bool isFlip)
{

	image = new Image[5];
	
	pos = { 0.0f, 0.0f };
	moveSpeed = 5.0f;
		
	for (int i = 0; i < 5; i++)
	{
		if (FAILED(image[i].Init(info.spriteSheet[i].filename,
			info.spriteSheet[i].width, info.spriteSheet[i].height,
			info.spriteSheet[i].maxFrameX, info.spriteSheet[i].maxFrameY,
			info.spriteSheet[i].isTransparent, info.spriteSheet[i].transColor)))
		{
			MessageBox(g_hWnd, info.spriteSheet[i].filename, TEXT("Warning"), MB_OK);
		}
	}


	health = info.health;
	weakPunchDamage = info.weakPunchDamage;
	weakKickDamage = info.weakKickDamage;
	strongPunchDamage = info.strongPunchDamage;
	strongKickDamage = info.strongKickDamage;
	characterName = info.characterName;
	this->isFlip = isFlip;

	hitRect = RECT{ 0, 0, 50, 100 };
	// hitRect = RECT{ 0, 0, info.spriteSheet[0].width/info.spriteSheet[0].maxFrameX, info.spriteSheet[0].height/info.spriteSheet[0].maxFrameY};
	attackRect = RECT{ 0, 0, 0,0 };

	this->isMoveable = isMoveable;
	elaspedFrame = 0.0f;
	currAnimaionFrame = 0;
	isWeakPunching = false;
	
}

void KOF_Character::Release()
{
	delete[] image;
}

void KOF_Character::Update()
{


	float frameSpeed = 20.0f;

	elaspedFrame += frameSpeed;

	if (elaspedFrame >= 100.0f)
	{
		currentFrameIndex++;

		elaspedFrame = RESET;
	}

	if (currentFrameIndex >= 15 && currentActionState == static_cast<int>(State::Idle))
	{
		currentFrameIndex = RESET;
	}

	switch (currentActionState)
	{
	case static_cast<int>(State::StrongPunch):
		if (currentFrameIndex >= 6)
		{
			currentFrameIndex = RESET;
			currentActionState = static_cast<int>(State::Idle);
		}
		break;
	case static_cast<int>(State::StrongKick):
		if (currentFrameIndex >= 7)
		{
			currentFrameIndex = RESET;
			currentActionState = static_cast<int>(State::Idle);
		}
		break;
	}


	// D key : 앞이동
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))
	{
		currentFrameIndex = RESET;
		currentActionState = static_cast<int>(State::MovingFoward);
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
	{
		pos.x += 2.0f * (frameSpeed / moveSpeed);
		if (currentFrameIndex >= 6)
		{
			currentFrameIndex = RESET;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(0x44))
	{
		currentFrameIndex = RESET;
		currentActionState = static_cast<int>(State::Idle);
	}


	// A Key : 뒤로 이동
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x41))
	{
		currentFrameIndex = 0;
		currentActionState = static_cast<int>(State::MovingBack);
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
	{
		pos.x -= 2.0f * (frameSpeed / moveSpeed);

		if (currentFrameIndex >= 6)
		{
			currentFrameIndex = RESET;
		}
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(0x41))
	{
		currentFrameIndex = RESET;
		currentActionState = static_cast<int>(State::Idle);
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
	// 히트박스 확인용
	//if (currentActionState == static_cast<int>(State::Idle))
		RenderRect(hdc, pos.x + 27, pos.y, 38, 94);


	if (image)
		image[currentActionState].Render(hdc,pos.x,pos.y,currentFrameIndex,isFlip);

	// 히트박스 확인용
	if (currentActionState == static_cast<int>(State::StrongKick))
		//RenderRect(hdc, pos.x + 107, pos.y, 25, 94);
		RenderRect(hdc,(int)(pos.x + 100 ), (int)(pos.y), 20 ,  100);
		

	if (currentActionState == static_cast<int>(State::StrongPunch))
		//RenderRect(hdc, pos.x + 97, pos.y, 20, 94);
		RenderRect(hdc, (int)(pos.x + 100), (int)(pos.y),  20 ,  100);


}


void KOF_Character::WeakPunch()
{
    
}

void KOF_Character::StrongPunch()
{
	if (currentActionState == static_cast<int>(State::StrongPunch)) return;
	currentFrameIndex = RESET;
	currentActionState = static_cast<int>(State::StrongPunch);
	currentCombatInfo.damage = strongPunchDamage;
	currentCombatInfo.hitRect = RECT{ (int)(pos.x + 100), (int)(pos.y),  (int)(pos.x + 100) + 20 , (int)pos.y + 100 };

	elaspedFrame = RESET;
}

void KOF_Character::WeakKick()
{

}

void KOF_Character::StrongKick()
{
	if (currentActionState == static_cast<int>(State::StrongKick)) return;
	currentFrameIndex = RESET;
	currentActionState = static_cast<int>(State::StrongKick);
	currentCombatInfo.damage = strongKickDamage;
	currentCombatInfo.hitRect = RECT{ (int)(pos.x + 100), (int)(pos.y),  (int)(pos.x + 100) + 20 , (int)pos.y + 100 };

	elaspedFrame = RESET;
}

bool KOF_Character::Guard(bool)
{
	return true;
}

void KOF_Character::GetDamage(int damage)
{
    health -= damage;
}

//TODO:
void KOF_Character::Move()
{
    pos.x += moveSpeed;
}

void KOF_Character::Move(int dirX)
{
    pos.x += moveSpeed * dirX;
    UpdateRect(hitRect, pos);
}

int KOF_Character::GetHealth() { return health; }


RECT KOF_Character::GetHitRect() { return hitRect; }

RECT KOF_Character::GetAttackRect() { return attackRect; }
