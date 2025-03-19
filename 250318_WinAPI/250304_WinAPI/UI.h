#pragma once

#include "GameObject.h"
class KOF_Character;

class UI : public GameObject
{
private:
	int healthForBoxWidth;				//체력바 테두리길이 변수, 초기화 이후 업데이트 하지 않음
	int HealthForUpdate;				//체력 업데이트용 변수
	int boxHeight;
	POINT boxPos;
public:
	void displayHealth(HDC hdc, int characterHealth);									//체력
	void displayHealth_BoxOutline(HDC hdc, int characterHealth);						//체력바
	void displayPortrait(HDC hdc, KOF_Character* targetCharacter);						//캐릭터 초상화
	bool winner(HDC hdc);																//승자

	void updateCharacterHealth(KOF_Character* targetCharacter);					//체력
	void updateBoxWidth(KOF_Character* targetCharacter);						//체력바
	inline int getTargetCharacterHealth() const { return HealthForUpdate; }	//캐릭터 체력 가져오기

	void Init(KOF_Character* targetCharacter);
	UI();
	~UI();
	void Update();
	void Render(HDC hdc);					//체력 렌더링
	void RenderBoxOutline(HDC hdc);			//체력바 렌더링
};

