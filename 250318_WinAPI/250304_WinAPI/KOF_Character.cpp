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
	this->isFlip = isFlip;
	this->playerNum = playerNum;


	switch (playerNum)
	{
	case 1:
		MOVEFOWARD = 'd';
		MOVEBACKWARD = 'a';

		ATTACK_WEAK_PUNCH = 'g';
		ATTACK_STRONG_PUNCH = 't';
		ATTACK_WEAK_KICK = 'h';
		ATTACK_STRONG_KICK = 'y';

		break;
	case 2:
		MOVEFOWARD = 'l';
		MOVEBACKWARD = '\'';

		ATTACK_WEAK_PUNCH = '5';
		ATTACK_STRONG_PUNCH = '8';
		ATTACK_WEAK_KICK = '6';
		ATTACK_STRONG_KICK = '9';

		break;
	}


	elaspedFrame = 0.0f;
	currAnimaionFrame = 0;
	isWeakPunching = false;

	KOF_CharacterStateIdle idleState;
	idleState.Init(this);

	KOF_CharacterStateMove moveState;
	moveState.Init(this);

	KOF_CharacterStateAttack attackState;
	attackState.Init(this);
	
	KOF_CharacterStateGuard guardState;
	guardState.Init(this);

	states = new KOF_CharacterFiniteStateMachineState[4]{
		idleState, moveState, attackState, guardState 
	};
	fsm->Init(states);

}

void KOF_Character::Release()
{
	delete[] image;
}

void KOF_Character::Update()
{
	fsm->Update();
	currentActionState = fsm->GetState();

		switch (currentActionState)
		{
		case static_cast<int>(State::Idle):
			
			if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_WEAK_PUNCH)) 
				fsm->SetState(static_cast<int>(State::AttackWeakPunch));
			else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_STRONG_PUNCH)) 
				fsm->SetState(static_cast<int>(State::AttackStrongPunch));
			else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_WEAK_KICK)) 
				fsm->SetState(static_cast<int>(State::AttackWeakKick));
			else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_STRONG_KICK)) 
				fsm->SetState(static_cast<int>(State::AttackStrongKick));

			else if (KeyManager::GetInstance()->IsStayKeyDown(MOVEFOWARD) ) 
				fsm->SetState(static_cast<int>(State::MovingFoward));
			else if (KeyManager::GetInstance()->IsStayKeyDown(MOVEBACKWARD))
			{
				// if enemy close
				//fsm->SetState(Guard);
				// else4
				// move backward
				fsm->SetState(static_cast<int>(State::MovingBackward));
			}
		break;
		case static_cast<int>(State::MovingFoward): case static_cast<int>(State::MovingBackward):

		if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_WEAK_PUNCH))
			fsm->SetState(static_cast<int>(State::AttackWeakPunch));
		else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_STRONG_PUNCH))
			fsm->SetState(static_cast<int>(State::AttackStrongPunch));
		else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_WEAK_KICK))
			fsm->SetState(static_cast<int>(State::AttackWeakKick));
		else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_STRONG_KICK))
			fsm->SetState(static_cast<int>(State::AttackStrongKick));

		else if (KeyManager::GetInstance()->IsOnceKeyUp(MOVEFOWARD) || KeyManager::GetInstance()->IsOnceKeyUp(MOVEBACKWARD))
		{
			fsm->SetState(static_cast<int>(State::Idle));
		}
		break;
	case static_cast<int>(State::AttackStrongKick):
		// exit on animation ends
		
		
		break;

	case static_cast<int>(State::AttackStrongPunch):
		// exit on animation ends
		break;
	case static_cast<int>(State::AttackWeakKick):
		// exit on animation ends
		break;
	case static_cast<int>(State::AttackWeakPunch):
		// exit on animation ends
		break;

	case static_cast<int>(State::Guard):
		if (KeyManager::GetInstance()->IsOnceKeyUp(MOVEBACKWARD))
		{
			fsm->SetState(static_cast<int>(State::Idle));
		}
		break;
	default: ;
	}
	



	float frameSpeed = 20.0f;

	elaspedFrame += frameSpeed;

	if (elaspedFrame >= 100.0f)
	{
		currentFrameIndex++;

		elaspedFrame = RESET;
	}



}

void KOF_Character::Render(HDC hdc)
{
	fsm->Render(hdc);

}


void KOF_Character::WeakPunch()
{
    
}

void KOF_Character::StrongPunch()
{
	if (currentActionState == static_cast<int>(State::AttackStrongPunch)) return;
	currentFrameIndex = RESET;
	currentActionState = static_cast<int>(State::AttackStrongPunch);
	currentCombatInfo.damage = strongPunchDamage;
	currentCombatInfo.hitRect = RECT{ (int)(pos.x + 100), (int)(pos.y),  (int)(pos.x + 100) + 20 , (int)pos.y + 100 };

	elaspedFrame = RESET;
}

void KOF_Character::WeakKick()
{

}

void KOF_Character::StrongKick()
{
	if (currentActionState == static_cast<int>(State::AttackStrongKick)) return;
	currentFrameIndex = RESET;
	currentActionState = static_cast<int>(State::AttackStrongKick);
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

void KOF_Character::LoopFrame(int frameIndexMax)
{
	currentFrameIndex = currentFrameIndex > frameIndexMax ? RESET : currentFrameIndex++;
}

void KOF_Character::ResetFrame()
{
	currentFrameIndex = 0;
}

void KOF_Character::ReturnToIdle()
{
	fsm->SetState(static_cast<int>(State::Idle));
	currentActionState = fsm->GetState();
}
