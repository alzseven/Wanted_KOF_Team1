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

	Image* image;
	int currentFrameIndex;

public:

	void WeakPunch();
	void StrongPunch();
	void WeakKick();
	void StrongKick();
	bool Guard(bool);

	void Init();
	void Release();
	void Update();
	void Render(HDC);




};

