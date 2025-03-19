#pragma once
#include "GameObject.h"

class Image;

class KOF_Character: public GameObject
{
private:
	int health;
	int weakPunchDamage;
	int weakKickDamage;
	int strongPunchDamage;
	int strongKickDamage;
	FPOINT Pos;
	float moveSpeed;
	string characterName;

	Image* image;
	int currentFrameIndex;
	int currentActionIndex;
	float elaspedFrame;

	combatInfo* combat;

public:
	void WeakPunch();
	void StrongPunch();

	void WeakKick();
	void StrongKick();

	bool Guard(bool isSuccess);

	inline combatInfo* CombatInfo() { return combat;}

	void Init();		// ³ª
	void Release();		// ³ª
	void Update();
	void Render(HDC hdc);
};

