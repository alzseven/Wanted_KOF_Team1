#pragma once
#include "GameObject.h"

class Image;
class KOF_Character;

class UI : public GameObject
{
private:
    Image* HpBar;
    

    Image* character1HpBarNotValid;
    Image* character2HpBarNotValid;
    
    Image* character1Portrait;
    Image* character2Portrait;

    Image* character1HpValid;
    Image* character2HpValid;

    KOF_Character* character1;
    KOF_Character* character2;


    int portraitOffset;
    int HpBarOffset;

    int HpBarSize;
    
    float character1LeftHp;
    float character2LeftHp;


    
public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    void Init(KOF_Character* character1, KOF_Character* character2);


};
