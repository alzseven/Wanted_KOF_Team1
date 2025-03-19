#include "UI.h"

#include "CommonFunction.h"
#include "KOF_Character.h"

void UI::Init()
{
}

void UI::Release()
{
}

void UI::Update()
{
    
}

void UI::Render(HDC hdc)
{
    RenderRectAtCenter(hdc,centerX, 100, 400, 80);
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    RenderRectAtCenter(hdc,centerX + 400 - 4 * character->GetHealth(), 100, 4 * character->GetHealth(), 80);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

void UI::Init(KOF_Character* character)
{
    this->character = character;
}

void UI::Init(KOF_Character* character, int centerX)
{
    this->centerX = centerX;
    this->character = character;
}