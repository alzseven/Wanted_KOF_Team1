#include "UI.h"
#include "KOF_Character.h"
#include "CommonFunction.h"

void UI::displayPortrait(HDC hdc, KOF_Character* targetCharacter)
{
	
}

void UI::winner(HDC hdc, bool isWin)
{
	
}

//void UI::updateCharacterHealth(KOF_Character* targetCharacter)
//{
//	HealthForUpdate = targetCharacter->getCurrentHealth();
//}
//
//void UI::updateBoxWidth(KOF_Character* targetCharacter)
//{
//	healthForBoxWidth = targetCharacter->getCurrentHealth();
//}

void UI::Init_myCharacter()
{
	/*updateCharacterHealth(targetCharacter);
	updateBoxWidth(targetCharacter);*/

	HealthForUpdate = myCharacter->getCurrentHealth();				//남은 체력에 비례해서 조절해야함
	healthForBoxWidth = myCharacter->getMaxHealth();			//수식을 모르겠어서 일단 400으로 설정함
	boxPos.x = 50;
	boxPos.y = 15;
	boxHeight = 30;
	percentage = 0;
}

void UI::Init_hostile()
{
	HealthForUpdate = hostileCharacter->getCurrentHealth();
	healthForBoxWidth = hostileCharacter->getMaxHealth();
	boxPos.x = WINSIZE_X - 50 - healthForBoxWidth;
	boxPos.y = 15;
	boxHeight = 30;
	percentage = 0;
}

void UI::Update()
{
	myCharacter->SetHealth(myCharacter->getCurrentHealth() - 10);	//상수(10)는 체력을 깔 데미지
	Update_HealthBar(myCharacter);
}

void UI::Update_hostile()
{
	hostileCharacter->SetHealth(hostileCharacter->getCurrentHealth() - 0.01f);
	Update_HealthBar(hostileCharacter);
}

UI::UI()
{

}

UI::~UI()
{

}

void UI::Update_HealthBar(KOF_Character* targetCharacter)
{
	float maxHp = (float)targetCharacter->getMaxHealth();
	float currHp = (float)targetCharacter->getCurrentHealth();
	percentage = (maxHp - currHp) / maxHp * (float)healthForBoxWidth;

	//percentage = (targetCharacter->getMaxHealth() - targetCharacter->getCurrentHealth())/targetCharacter->getMaxHealth();
	
}

void UI::Render_HealthBar(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));		//KOF_03 원판과 유사하게 초록색으로 설정함
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, boxPos.x + percentage, boxPos.y, healthForBoxWidth - percentage, boxHeight);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void UI::Render_HealthBar_Hostile(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, boxPos.x, boxPos.y, healthForBoxWidth - percentage, boxHeight);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void UI::RenderBoxOutline(HDC hdc)
{
	RenderRect(hdc, boxPos.x, boxPos.y, healthForBoxWidth,boxHeight);
}

