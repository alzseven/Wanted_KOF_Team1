#pragma once
#include "GameObject.h"

class Image;

class KOF_Character : public GameObject
{
	int health;
	int maxHealth;
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
	Image* portrait;
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
	inline int getCurrentHealth() { return health; };
	inline int getMaxHealth() { return maxHealth; };

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	KOF_Character();
	~KOF_Character();

	void SetHealth(int newHealth);
};