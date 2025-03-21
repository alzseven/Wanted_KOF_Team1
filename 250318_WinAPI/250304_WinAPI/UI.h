﻿#pragma once
#include "GameObject.h"

class Image;
class KOF_Character;

class UI : public GameObject
{
private:
    Image* HpBar;
    Image* HpBarValid;
    Image* HpBarNotValid;

    KOF_Character* character;
    FPOINT pos;
    int centerX;
    
public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    void Init(KOF_Character* character);
    void Init(KOF_Character* character, int centerX);

    UI();
    ~UI();
};
