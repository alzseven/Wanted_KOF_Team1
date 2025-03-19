#include "UI.h"
#include "KOF_Character.h"
#include "CommonFunction.h"

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

	HealthForUpdate = 400;				//���� ü�¿� ����ؼ� �����ؾ���
	healthForBoxWidth = 400;			//������ �𸣰ھ �ϴ� 400���� ������
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

void UI::Render_Update_HealthBar(HDC hdc, KOF_Character* targetCharacter)
{
	percentage = 100 - targetCharacter->getHealth();

}

void UI::Render_HealthBar(HDC hdc)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));		//KOF_03 ���ǰ� �����ϰ� �ʷϻ����� ������
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	RenderRect(hdc, boxPos.x + percentage, boxPos.y, healthForBoxWidth - percentage, boxHeight);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void UI::RenderBoxOutline(HDC hdc)
{
	RenderRect(hdc, boxPos.x, boxPos.y, healthForBoxWidth,boxHeight);
}

