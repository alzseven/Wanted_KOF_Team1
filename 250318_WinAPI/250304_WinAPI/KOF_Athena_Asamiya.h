#pragma once
#include "GameObject.h"

class Image;

class KOF_Athena_Asamiya : public GameObject
{
	int health;
	int weakPunchDamage;
	int weakKickDamage;
	int strongPunchDamage;
	int strongKickDamage;
	float moveSpeed;
	float jump;
	string characterName;
	FPOINT Pos;
	RECT hitRect;
	RECT attackRect;

	Image* image;
	int currentFrameIndex;

public:
	void WeakPunch();
	void StrongPunch();
	void WeakKick();
	void StrongKick();
	void Guard(bool isBlock);
	void Move(int posX, int posY);
	inline int getMoveSpeed() { return moveSpeed; };
	inline int getJump() { return jump; };

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	KOF_Athena_Asamiya() = default;
	~KOF_Athena_Asamiya();
};