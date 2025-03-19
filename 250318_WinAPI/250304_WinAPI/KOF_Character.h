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
	RECT hitRect;    // �ǰݹ���
	RECT attackRect; // ���ݹ���
	Image* image;
	int currentFrameIndex;
	int currentActionIndex;
	float elaspedFrame;

	combatInfo* combat;

public:
	void WeakPunch(RECT& hitRect, RECT& attackRect, int& damage);
	void StrongPunch(RECT& hitRect, RECT& attackRect, int& damage);

	void WeakKick(RECT& hitRect, RECT& attackRect, int& damage);	// ��
	void StrongKick(RECT& hitRect, RECT& attackRect, int& damage);


	void WeakPunch();
	void StrongPunch();

	void WeakKick();
	void StrongKick();

	bool Guard(bool isSuccess);

	void Init();		// ��
	void Release();		// ��
	void Update();
	void Render(HDC hdc);
};

