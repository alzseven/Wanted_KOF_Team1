#pragma once
#include "GameObject.h"


class Image;

class KOF_Character : public GameObject
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
	RECT hitRect;
	RECT attackRect;

	COMBATINFO combatInfo;
	UIINFO uiInfo;

	Image* image;
	int currentFrameIndex;
	// 현재 캐릭터의 상태 저장
	int currentActionState;
	float elaspedFrame;

public:

	void WeakPunch();
	void StrongPunch();
	void WeakKick();
	void StrongKick();
	bool Guard(bool);

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	COMBATINFO GetCombatInfo();
	UIINFO GetUIInfo();



};

