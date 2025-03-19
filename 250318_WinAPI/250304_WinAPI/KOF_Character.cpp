#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"

void KOF_Character::Init(/*ĳ���� �̸�, ĳ���� ������ �� ���ڷ� �޾Ƽ� �ʱ�ȭ ����� ��*/)
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
	
	// �ӽ�
	combatInfo = { {0,0,0,0}, {0,0,0,0}, 0};
	uiInfo = {"Mai", 100};

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
		MessageBox(g_hWnd, TEXT("Image/Mai_StrongPunch.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	if (FAILED(image[4].Init(TEXT("Image/Mai_Shiranui/Mai_StrongKick.bmp"), 979, 133, 7, 1,
		true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, TEXT("Image/Mai_StrongKick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

}

void KOF_Character::Release()
{
	delete[] image;
}

void KOF_Character::Update()
{

	// Update combatInfo
	// �ӽ� �ϵ��ڵ�
	combatInfo = { {static_cast<int>(Pos.x), static_cast<int>(Pos.y), 77, 94}, 
					{static_cast<int>(Pos.x),static_cast<int>(Pos.y + 97), 30,94},
					20 };

	// Update uiInfo
	// �ӽ�
	uiInfo = { characterName, health};


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


	// D key : ���̵�
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))
	{
		currentFrameIndex = RESET;
		currentActionState = static_cast<int>(State::MovingFoward);
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
	{
		Pos.x += 2.0f * (frameSpeed / moveSpeed);
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


	// A Key : �ڷ� �̵�
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x41))
	{
		currentFrameIndex = 0;
		currentActionState = static_cast<int>(State::MovingBack);
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
	{
		Pos.x -= 2.0f * (frameSpeed / moveSpeed);

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

	// J key : ����ġ
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x4A))
	{
		StrongPunch();
	}
	
	// K key : ����
	if (KeyManager::GetInstance()->IsOnceKeyDown(0x4B))
	{
		StrongKick();
	}
	


}

void KOF_Character::Render(HDC hdc)
{
	// ��Ʈ�ڽ� Ȯ�ο�
	//if (currentActionState == static_cast<int>(State::Idle))
		RenderRect(hdc, Pos.x + 27, Pos.y, 38, 94);

	if (image)
		image[currentActionState].Render(hdc,Pos.x,Pos.y,currentFrameIndex,false);

	// ��Ʈ�ڽ� Ȯ�ο�
	if (currentActionState == static_cast<int>(State::StrongKick))
		RenderRect(hdc, Pos.x + 107, Pos.y, 25, 94);
	 
	if (currentActionState == static_cast<int>(State::StrongPunch))
		RenderRect(hdc, Pos.x + 97, Pos.y, 20, 94);

}


void KOF_Character::WeakPunch()
{

}

void KOF_Character::StrongPunch()
{
	if (currentActionState == static_cast<int>(State::StrongPunch)) return;
	currentFrameIndex = RESET;
	currentActionState = static_cast<int>(State::StrongPunch);
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
	elaspedFrame = RESET;
}

bool KOF_Character::Guard(bool)
{
	return true;
}


COMBATINFO KOF_Character::GetCombatInfo()
{
	return combatInfo;
}

UIINFO KOF_Character::GetUIInfo()
{
	return uiInfo;
}
