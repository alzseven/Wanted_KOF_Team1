#pragma once
#include "GameObject.h"

class Background;
class UI;
class KOF_Character;

class GameManager : public GameObject
{
private:
    Background* background;
    KOF_Character* character1;
    KOF_Character* character2;
    UI* character1UI;
    UI* character2UI;
    
public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);
    
};
