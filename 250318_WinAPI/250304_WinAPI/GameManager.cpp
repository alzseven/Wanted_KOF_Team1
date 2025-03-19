﻿#include "GameManager.h"

#include "Background.h"
#include "CommonFunction.h"
#include "KOF_Character.h"
#include "UI.h"


void GameManager::Init()
{
    // Background Init
    background = new Background();
    background->Init();

    // Character Init
    // TODO: Set random two characters how?
    CharacterInfo charinfo = CharacterInfo{
        100, 5, 7, 10, 14,
        "Chang", new SpriteSheetInfo[]{
            SpriteSheetInfo{
                "Move",
            TEXT("Image/chang_move.bmp"),
            2100,188,10,1,true,RGB(255,0,255),
        },
        SpriteSheetInfo{
            "punch_weak",
        TEXT("Image/chang_punch_weak.bmp"),
        1050,188,5,1,true,RGB(255,0,255),
        }
        
        }
    };
    
    character1 = new KOF_Character();
    character1->Init(charinfo, true);
    character1->SetPos({200, 300});
    
    character2 = new KOF_Character();
    character2->Init(charinfo, false);
    character2->SetPos({500, 300});

    // UI Init
    character1UI = new UI;
    character1UI->Init(character1, 200);
    character2UI = new UI;
    character2UI->Init(character2, 800);
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
    // if (character1->GetHealth() <= 0 || character2->GetHealth() <= 0)
    // {
    //     //TODO: Game End, Do Something
    //     int winnerPlayerIndex = character1->GetHealth() <= 0 ? 2 : 1;
    //     
    // }
    // else
    // {
        background->Update();
        
        character1->Update();
        // character2->Update();

        character1UI->Update();
        character2UI->Update();
    // }

    // Handle Collision
    CheckCollisions();
}

void GameManager::CheckCollisions()
{
    // Attacker - character2, hit - character1
    if (RectInRect(character2->GetCurrentAttack().hitRect, character1->GetHitRect()))
    {
        character1->GetDamage(character2->GetCurrentAttack().damage);
    }
    
    // Attacker - character1, hit - character2
    if (RectInRect(character1->GetCurrentAttack().hitRect, character2->GetHitRect()))
    {
        character2->GetDamage(character1->GetCurrentAttack().damage);
        character1->ResetAttack();
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
