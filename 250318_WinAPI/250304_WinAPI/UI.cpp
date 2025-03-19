#include "UI.h"
#include "KOF_Character.h"
#include "CommonFunction.h"

void UI::displayHealth(HDC hdc, int characterHealth)
{
	RenderRect(hdc, 10, 10, characterHealth, 15);
}

void UI::displayHealth_BoxOutline(HDC hdc, int characterHealth)
{
	RenderRect(hdc, 10, 10, characterHealth, 15);
}

void UI::displayPortrait(HDC hdc, KOF_Character* targetCharacter)
{
}

bool UI::winner(HDC hdc)
{
	return false;
}

void UI::updateCharacterHealth(KOF_Character* targetCharacter)
{
	HealthForUpdate = targetCharacter->getHealth();
}

void UI::updateBoxWidth(KOF_Character* targetCharacter)
{
	healthForBoxWidth = targetCharacter->getHealth();
}

void UI::Init(KOF_Character* targetCharacter)
{
	/*updateCharacterHealth(targetCharacter);
	updateBoxWidth(targetCharacter);*/

	HealthForUpdate = 400;
	healthForBoxWidth = 400;
	boxPos.x = 10;
	boxPos.y = 15;
	boxHeight = 30;
}

UI::UI()
{

}

UI::~UI()
{

}

void UI::Update()
{
	
}

void UI::Render(HDC hdc)
{
	RenderRect(hdc, boxPos.x, boxPos.y, 250, boxHeight);
}

void UI::RenderBoxOutline(HDC hdc)
{
	RenderRect(hdc, boxPos.x, boxPos.y, healthForBoxWidth,boxHeight);
}