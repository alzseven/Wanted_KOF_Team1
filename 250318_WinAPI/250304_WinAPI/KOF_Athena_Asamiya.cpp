#include "KOF_Athena_Asamiya.h"
#include "Image.h"
#include "CommonFunction.h"

void KOF_Athena_Asamiya::WeakPunch()
{
	//if (RectInRect(hitRect, ))	//�� ĳ������ ������ �־�� ���� �ʳ�?
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
	hitRect = { 10, 10, 10, 10 };			//���Ƿ� ����
	attackRect = { 10, 10, 10, 10 };		//���Ƿ� ����
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
	//���� �����س� ������ ���� ������ �ڵ尡 �־��µ� �н���
	//��������Ʈ �밡�� ����� �𸣰ڴ�
}

void KOF_Athena_Asamiya::Render(HDC hdc)
{
	if (image)
		image->Render(hdc, Pos.x, Pos.y, currentFrameIndex, true);
}

KOF_Athena_Asamiya::~KOF_Athena_Asamiya()
{

}
