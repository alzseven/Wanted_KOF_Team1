#pragma once

#include "GameObject.h"
class KOF_Character;

class UI : public GameObject
{
private:
	int healthForBoxWidth;				//ü�¹� �׵θ����� ����, �ʱ�ȭ ���� ������Ʈ ���� ����
	int HealthForUpdate;				//ü�� ������Ʈ�� ����
	int boxHeight;
	POINT boxPos;
public:
	void displayHealth(HDC hdc, int characterHealth);									//ü��
	void displayHealth_BoxOutline(HDC hdc, int characterHealth);						//ü�¹�
	void displayPortrait(HDC hdc, KOF_Character* targetCharacter);						//ĳ���� �ʻ�ȭ
	bool winner(HDC hdc);																//����

	void updateCharacterHealth(KOF_Character* targetCharacter);					//ü��
	void updateBoxWidth(KOF_Character* targetCharacter);						//ü�¹�
	inline int getTargetCharacterHealth() const { return HealthForUpdate; }	//ĳ���� ü�� ��������

	void Init(KOF_Character* targetCharacter);
	UI();
	~UI();
	void Update();
	void Render(HDC hdc);					//ü�� ������
	void RenderBoxOutline(HDC hdc);			//ü�¹� ������
};

