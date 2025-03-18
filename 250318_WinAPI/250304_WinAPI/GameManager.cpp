#include "GameManager.h"

#include "Background.h"
#include "KOF_Character.h"
#include "UI.h"

void GameManager::Init()
{
    // Background Init
    background = new Background();
    background->Init();

    // Character Init
    // TODO: Set random two characters how?
    character1 = new KOF_Character();
    character1->Init();
    character2 = new KOF_Character();
    character2->Init();

    // UI Init
    character1UI = new UI;
    character1UI->Init();
    character2UI = new UI;
    character2UI->Init();
}

void GameManager::Release()
{
    // Release and Delete BackGround;
    background->Release();
    delete background;

    // Release and Delete UIs;
    character1UI->Release();
    delete character1UI;
    character2UI->Release();
    delete character2UI;
    
    // Release and Delete Characters;
    character1->Release();
    delete character1;
    character2->Release();
    delete character2;

}

void GameManager::Update()
{
    if (character1->GetHealth() <= 0 || character2->GetHealth() <= 0)
    {
        //TODO: Game End, Do Something
        int winnerPlayerIndex = character1->GetHealth() <= 0 ? 2 : 1;
        
    }
    else
    {
        background->Update();
        
        character1->Update();
        character2->Update();

        character1UI->Update();
        character2UI->Update();
    }
}

void GameManager::Render(HDC hdc)
{
    background->Render(hdc);

    character1->Render(hdc);
    character2->Render(hdc);

    character1UI->Render(hdc);
    character2UI->Render(hdc);
}
