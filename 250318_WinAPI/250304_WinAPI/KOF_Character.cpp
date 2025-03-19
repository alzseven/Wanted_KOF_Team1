#include "KOF_Character.h"
#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"

void KOF_Character::WeakPunch(RECT& hitRect, RECT& attackRect, int& damage)		// ��
{
	// Rect�� ��ȯ
	// �������� ��ߵ�
	UpdateRect(this->hitRect, {Pos.x, Pos.y});		// ĳ���͸��� �ٸ�
	UpdateRect(this->attackRect, { Pos.x + 10, Pos.y - 20 });	// ĳ���͸��� �ٸ�

	hitRect = this->hitRect;
	attackRect = this->attackRect;
	damage = weakKickDamage;
}

void KOF_Character::StrongPunch()
{
}

void KOF_Character::WeakKick(RECT &hitRect, RECT &attackRect, int &damage)		// ��
{
	// ���� �Ŵ������� ȣ���, ĳ������ �ǰ�, ���� rect ��ȯ, ������ ���� ��ȯ...
	// Rect
	UpdateRect(this->hitRect, { Pos.x, Pos.y });
	UpdateRect(this->attackRect, { Pos.x + 10, Pos.y + 20 });

	hitRect = this->hitRect;
	attackRect = this->attackRect;
	damage = weakKickDamage;
}

void KOF_Character::StrongKick()
{
}

bool KOF_Character::Guard(bool isSuccess)
{
	return false;
}

void KOF_Character::Init()		// ��
{
	health = 100;
	weakPunchDamage = 5;
	weakKickDamage = 5;
	strongPunchDamage = 10;
	strongKickDamage = 10;
	Pos = {0.0f, 0.0f};
	moveSpeed = 5.0f;
	characterName = "King";
	hitRect =GetRectAtCenter(Pos.x, Pos.y, 20, 110);    // �ǰݹ��� - ���߿� UpdateRect�� ��ġ�� �°� ������Ʈ
	attackRect = GetRectAtCenter(Pos.x, Pos.y, 5, 5); // ���ݹ��� - ��������
	
	//image = new Image;
	//if (FAILED(image->Init(TEXT("Image/kingStrongKick.bmp"), 1000, 110, 10, 1,
	//	true, RGB(103, 167, 141))))
	//{
	//	MessageBox(g_hWnd, TEXT("Image/kingStrongKick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	//}

	currentFrameIndex = 0;
	currentActionIndex = 0;
	elaspedFrame = 0.0f;

	image = new Image[5];

	if (FAILED(image[0].Init(TEXT("Image/kingDefault.bmp"), 700, 110, 7, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingDefault.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	if (FAILED(image[1].Init(TEXT("Image/kingWeakPunch.bmp"), 500, 110, 5, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingWeakPunch.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	if (FAILED(image[2].Init(TEXT("Image/kingWeakKick.bmp"), 500, 110, 5, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingWeakKick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	if (FAILED(image[3].Init(TEXT("Image/kingStrongPunch.bmp"), 600, 130, 6, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingStrongPunch.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}

	if (FAILED(image[4].Init(TEXT("Image/kingStrongKick.bmp"), 1000, 110, 10, 1,
		true, RGB(103, 167, 141))))
	{
		MessageBox(g_hWnd, TEXT("Image/kingStrongKick.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
	}
}

void KOF_Character::Release()		// ��
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


	// D key : ���̵�
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


	// A Key : �ڷ� �̵�
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
	RenderRectAtCenter(hdc, Pos.x, Pos.y, 5, 5);
}
