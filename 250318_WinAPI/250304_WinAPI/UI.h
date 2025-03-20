#pragma once

#include "GameObject.h"
class KOF_Character;

class UI : public GameObject
{
private:
	int healthForBoxWidth;				//ü�¹ڽ� �׵θ����� ����, �ʱ�ȭ ���� ������Ʈ ���� ����
	int HealthForUpdate;				//ü�� ������Ʈ�� ����
	int boxHeight;
	POINT boxPos;
	float percentage;
	KOF_Character* myCharacter;
	KOF_Character* hostileCharacter;
public:
	void displayPortrait(HDC hdc, KOF_Character* targetCharacter);						//ĳ���� �ʻ�ȭ
	void winner(HDC hdc, bool isWin);																//����

	//void updateCharacterHealth(KOF_Character* targetCharacter);					//ü��
	//void updateBoxWidth(KOF_Character* targetCharacter);						//ü�¹ڽ�
	inline int getTargetCharacterHealth() const { return HealthForUpdate; }	//ĳ���� ü�� ��������
	inline int getPercentage() const { return percentage; }

	void Init_myCharacter();
	void Init_hostile();
	void Update();
	void Update_hostile();
	UI();
	~UI();
	void Update_HealthBar(KOF_Character* targetCharacter);
	void Render_HealthBar(HDC hdc);					//ü�� ������
	void Render_HealthBar_Hostile(HDC hdc);			//���� ü�� ������
	void RenderBoxOutline(HDC hdc);					//ü�¹ڽ� ������
};

