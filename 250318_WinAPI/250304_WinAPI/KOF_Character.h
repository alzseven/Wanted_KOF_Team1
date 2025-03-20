#pragma once
#include "GameObject.h"

class Image;
enum State
{
	Idle,
	Walk,
	Weakpunch,
	Strongpunch,
	Weakkick,
	Strongkick,
	Defense
};

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
	int elapsedFrame;

public:

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void WeakPunch();
	void StrongPunch();
	void WeakKick();
	void StrongKick();
	void Guard(bool);


};

