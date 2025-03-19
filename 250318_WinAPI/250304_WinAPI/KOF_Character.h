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
	RECT hitRect;    // 피격범위
	RECT attackRect; // 공격범위
	Image* image;
	int currentFrameIndex;
	int currentActionIndex;
	float elaspedFrame;

	combatInfo* combat;

public:
	void WeakPunch(RECT& hitRect, RECT& attackRect, int& damage);
	void StrongPunch(RECT& hitRect, RECT& attackRect, int& damage);

	void WeakKick(RECT& hitRect, RECT& attackRect, int& damage);	// 나
	void StrongKick(RECT& hitRect, RECT& attackRect, int& damage);


	void WeakPunch();
	void StrongPunch();

	void WeakKick();
	void StrongKick();

	bool Guard(bool isSuccess);

	void Init();		// 나
	void Release();		// 나
	void Update();
	void Render(HDC hdc);
};

