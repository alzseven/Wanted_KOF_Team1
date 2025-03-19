#pragma once
#include "GameObject.h"

class Image;
class KOF_Character;

class UI : public GameObject
{
private:
    Image* image;
    KOF_Character* character;
    int centerX;
    
public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    void Init(KOF_Character* character);
    void Init(KOF_Character* character, int centerX);
};
