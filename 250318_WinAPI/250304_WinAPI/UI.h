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
	int percentage;
public:
	void displayPortrait(HDC hdc, KOF_Character* targetCharacter);						//ĳ���� �ʻ�ȭ
	bool winner(HDC hdc);																//����

	void updateCharacterHealth(KOF_Character* targetCharacter);					//ü��
	void updateBoxWidth(KOF_Character* targetCharacter);						//ü�¹�
	inline int getTargetCharacterHealth() const { return HealthForUpdate; }	//ĳ���� ü�� ��������

	void Init(KOF_Character* targetCharacter);
	UI();
	~UI();
	void Render_Update_HealthBar(HDC hdc, KOF_Character* targetCharacter);
	void Render_HealthBar(HDC hdc);					//ü�� ������
	void RenderBoxOutline(HDC hdc);			//ü�¹� ������
};

