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
    delete HpBarValid;
    delete HpBarNotValid;
}

void UI::Update()
{
    
}

void UI::Render(HDC hdc)
{
    if (!this->character->GetIsFlip())
    {
        HpBar->Render(hdc,0,0);
    }
    else
    {
        HpBar->Render(hdc,WINSIZE_X-WINSIZE_X/2.5,0);
    }
    

}

void UI::Init(KOF_Character* character)
{
    this->character = character;


}

void UI::Init(KOF_Character* character, int centerX)
{
    this->centerX = centerX;
    this->character = character;
  
    HpBar = new Image;
    HpBarValid = new Image;
    HpBarNotValid = new Image;

  

    if (this->character->GetIsFlip())
    {

        HpBar->Init(TEXT("Image/UI/HpBar2.bmp"), WINSIZE_X / 2.5, WINSIZE_Y / 5, true, RGB(255, 0, 255));

        pos.x = WINSIZE_X - WINSIZE_X / 2.5;
        pos.y = 0;
    }
    else
    {
        HpBar->Init(TEXT("Image/UI/HpBar1.bmp"), WINSIZE_X / 2.5, WINSIZE_Y / 5, true, RGB(255, 0, 255));
        pos.x = 0;
        pos.y = 0;

    }


       
    HpBarValid->Init(TEXT("Image/UI/HpValid.bmp"), 102, 6);
    HpBarNotValid->Init(TEXT("Image/UI/HpBarNotValid.bmp"), 102, 6);
    

}

UI::UI()
{

}

UI::~UI()
{
}
