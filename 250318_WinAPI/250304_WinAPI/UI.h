#pragma once

#include "GameObject.h"
class KOF_Character;

class UI : public GameObject
{
private:
	int healthForBoxWidth;				//체력박스 테두리길이 변수, 초기화 이후 업데이트 하지 않음
	int HealthForUpdate;				//체력 업데이트용 변수
	int boxHeight;
	POINT boxPos;
	float percentage;
public:
	void displayPortrait(HDC hdc, KOF_Character* targetCharacter);						//캐릭터 초상화
	void winner(HDC hdc, bool isWin);																//승자

	//void updateCharacterHealth(KOF_Character* targetCharacter);					//체력
	//void updateBoxWidth(KOF_Character* targetCharacter);						//체력박스
	inline int getTargetCharacterHealth() const { return HealthForUpdate; }	//캐릭터 체력 가져오기
	inline int getPercentage() const { return percentage; }

	void Init(KOF_Character* targetCharacter);
	void Init_hostile(KOF_Character* targetCharacter);
	UI();
	~UI();
	void Update_HealthBar(KOF_Character* targetCharacter);
	void Render_HealthBar(HDC hdc);					//체력 렌더링
	void Render_HealthBar_Hostile(HDC hdc);			//상대방 체력 렌더링
	void RenderBoxOutline(HDC hdc);					//체력박스 렌더링
};

