#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"
#include "Image.h"

void KOF_Character::Init(/*캐릭터 이름, 캐릭터 데미지 등 인자로 받아서 초기화 해줘야 함*/)
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
	currentActionState = 0;
	elaspedFrame = 0.0f;
    currentCombatInfo.damage = weakPunchDamage;
    currentCombatInfo.hitRect = hitRect;
    hitRect = RECT{ (int)(pos.x + 150), (int)(pos.y + 100), (int)(pos.x + 150)+85, (int)(pos.y + 100) + 30};
	
    // currentCombatInfo = COMBATINFO{ hitRect, weakPunchDamage};
    isWeakPunching = true;

	/*	image = new Image();
	if (FAILED(image->Init(TEXT("Image/Mai_Shiranui/Mai.bmp"), 1455, 627, 15, 5,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
	*/

	image = new Image[5];

	if (FAILED(image[0].Init(TEXT("Image/Mai_Shiranui/Mai_Idle.bmp"), 1455, 114, 15, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Idle.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	if (FAILED(image[1].Init(TEXT("Image/Mai_Shiranui/Mai_Back.bmp"), 552, 121, 6, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Back.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	if (FAILED(image[2].Init(TEXT("Image/Mai_Shiranui/Mai_Foward.bmp"), 648, 124, 6, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_Foward.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
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

    this->isMoveable = isMoveable;
    
    elapsedFrame = 0;
    currAnimaionFrame = 0;
}

{
}

{
        MessageBox(g_hWnd, info.spriteSheet[1].filename, TEXT("Warning"), MB_OK);
    }




	}
	
	{
	}

		{
		}
		break;
	}

	{
	{
		{
		}
            return;
	}
	{

	{
	}
	{

		{
		}
                elapsedFrame = 0;
	}
	if (KeyManager::GetInstance()->IsOnceKeyUp(0x41))
	{
		currentFrameIndex = RESET;
		currentActionState = static_cast<int>(State::Idle);
	}

	{
	}
	}
	


}

void KOF_Character::Render(HDC hdc)
{
	// 히트박스 확인용
	//if (currentActionState == static_cast<int>(State::Idle))
		RenderRect(hdc, Pos.x + 27, Pos.y, 38, 94);

	if (image)
		image[currentActionState].Render(hdc,Pos.x,Pos.y,currentFrameIndex,false);

	// 히트박스 확인용
	if (currentActionState == static_cast<int>(State::StrongKick))
		RenderRect(hdc, Pos.x + 107, Pos.y, 25, 94);
	 
	if (currentActionState == static_cast<int>(State::StrongPunch))
		RenderRect(hdc, Pos.x + 97, Pos.y, 20, 94);

}


void KOF_Character::WeakPunch()
{
        // RenderRect(hdc, pos.x + 150, pos.y + 100, 85, 30);
        // RenderRect(hdc, pos.x + 65 * ( pos.x > 400 ? -0 : 0), pos.y, 150, 180);
        punchImage->Render(hdc, pos.x + 65 * ( pos.x > 400 ? -0 : 0), pos.y, currAnimaionFrame, !isMoveable);

}

void KOF_Character::StrongPunch()
{
	if (currentActionState == static_cast<int>(State::StrongPunch)) return;
	currentFrameIndex = RESET;
	currentActionState = static_cast<int>(State::StrongPunch);
	elaspedFrame = RESET;
}

int KOF_Character::GetHealth() { return health; }

void KOF_Character::WeakKick()
{
RECT KOF_Character::GetHitRect() { return hitRect; }

}
RECT KOF_Character::GetAttackRect() { return attackRect; }

void KOF_Character::StrongKick()
{
	if (currentActionState == static_cast<int>(State::StrongKick)) return;
	currentFrameIndex = RESET;
	currentActionState = static_cast<int>(State::StrongKick);
	elaspedFrame = RESET;
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
