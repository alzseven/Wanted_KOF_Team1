#include "UI.h"

#include "CommonFunction.h"
#include "KOF_Character.h"
#include "Image.h"

void UI::Init()
{

}

void UI::Release()
{
    delete HpBar;


    delete character1HpValid;
    delete character2HpValid;

    delete character1HpBarNotValid;
    delete character2HpBarNotValid;

    delete character1Portrait;
    delete character2Portrait;
}

void UI::Update()
{

    if (character1)
    {
        float max = (float)character1->GetMaxHealth();
        float cur = (float)character1->GetHealth();
        character1LeftHp = ( cur / max) * (HpBarSize - HpBarOffset);
    }
    if (character2)
        character2LeftHp = ((float)character2->GetHealth() / (float)character1->GetMaxHealth()) * (HpBarSize - HpBarOffset);

}

void UI::Render(HDC hdc)
{
    if (HpBar)
        HpBar->Render(hdc, 0, 0);

    if(character1HpBarNotValid)
        character1HpBarNotValid->RenderRange(hdc, 71, 43, HpBarSize - HpBarOffset,9);
    if (character2HpBarNotValid)
    character2HpBarNotValid->RenderRange(hdc, 352, 43, HpBarSize - HpBarOffset,9);

    if(character1HpValid)
        character1HpValid->RenderRange(hdc,  71, 43, character1LeftHp , 9);
    if (character2HpValid)
        character2HpValid->RenderRange(hdc, 352 + (HpBarSize - HpBarOffset) - character2LeftHp , 43, character2LeftHp, 9);

    if (character1Portrait)
        character1Portrait->Render(hdc, -portraitOffset,-portraitOffset,0,false);
    if (character2Portrait)
       character2Portrait->Render(hdc, WINSIZE_X - WINSIZE_X / 8 + portraitOffset, 0,0,true);
    

}

void UI::Init(KOF_Character* character1, KOF_Character* character2)
{

    this->character1 = character1;
    this->character2 = character2;
  
    HpBar = new Image;

    character1HpValid = new Image;
    character2HpValid = new Image;

    character1HpBarNotValid = new Image;
    character2HpBarNotValid = new Image;

    character1Portrait = new Image;
    character2Portrait = new Image;

    portraitOffset = 5;
    HpBarOffset = 8;
    HpBarSize = 216;

    character1LeftHp = 200;
    character2LeftHp = 200;

    HpBar->Init(TEXT("Image/UI/HpBar.bmp"), WINSIZE_X , WINSIZE_Y / 5, true, RGB(255, 0, 255));

    std::string character1Name = character1->GetName();  
    std::wstring character1PortraitPath = L"Image/UI/" + std::wstring(character1Name.begin(), character1Name.end()) + L"_Portrait.bmp";
    character1Portrait->Init(character1PortraitPath.c_str(), WINSIZE_X / 8, WINSIZE_Y / 5, 1, 1, false);

    std::string character2Name = character2->GetName();
    std::wstring character2PortraitPath = L"Image/UI/" + std::wstring(character2Name.begin(), character2Name.end()) + L"_Portrait.bmp";
    character2Portrait->Init(character2PortraitPath.c_str(), WINSIZE_X / 8, WINSIZE_Y / 5, 1, 1, false);

    character1HpValid->Init(TEXT("Image/UI/HpValid.bmp"), 216, 9);
    character2HpValid->Init(TEXT("Image/UI/HpValid.bmp"), 216, 9);

    character1HpBarNotValid->Init(TEXT("Image/UI/HpBarNotValid.bmp"), 216, 9);
    character2HpBarNotValid->Init(TEXT("Image/UI/HpBarNotValid.bmp"), 216, 9);




}


