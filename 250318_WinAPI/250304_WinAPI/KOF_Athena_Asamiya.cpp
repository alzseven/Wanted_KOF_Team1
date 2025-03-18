#include "KOF_Athena_Asamiya.h"
#include "Image.h"
#include "CommonFunction.h"

void KOF_Athena_Asamiya::WeakPunch()
{
	//if (RectInRect(hitRect, ))	//적 캐릭터의 정보도 있어야 하지 않나?
	//{
	//}
}

void KOF_Athena_Asamiya::StrongPunch()
{
	if (RectInRect())
	{
	}
}

void KOF_Athena_Asamiya::WeakKick()
{
	if (RectInRect())
	{
	}
}

void KOF_Athena_Asamiya::StrongKick()
{
	if (RectInRect())
	{
	}
}

void KOF_Athena_Asamiya::Guard(bool isBlock)
{

}

void KOF_Athena_Asamiya::Move(int posX, int posY)
{
	this->Pos.x = posX;
	this->Pos.y = posY;
}

void KOF_Athena_Asamiya::Init()
{
	health = 100;
	weakPunchDamage = 10;
	weakKickDamage = 15;
	strongPunchDamage = 20;
	strongKickDamage = 25;
	moveSpeed = 5.0f;
	characterName = "Athena Asamiya";
	currentFrameIndex = 0;
	Pos = { 0.0f, 0.0f };
	hitRect = { 10, 10, 10, 10 };			//임의로 정함
	attackRect = { 10, 10, 10, 10 };		//임의로 정함
}

void KOF_Athena_Asamiya::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void KOF_Athena_Asamiya::Update()
{
	//내가 생각해낸 로직에 맞춰 구현한 코드가 있었는데 분실함
	//스프라이트 노가다 방법을 모르겠다
}

void KOF_Athena_Asamiya::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, Pos.x, Pos.y, currentFrameIndex, true);
}

KOF_Athena_Asamiya::~KOF_Athena_Asamiya()
{

}
