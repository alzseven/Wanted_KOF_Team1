#include "GameManager.h"

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
        100,
        5,
        7,
        10,
        14,
        "Mai",
        new SpriteSheetInfo[10]{
            SpriteSheetInfo{
                "Mai_Idle",
                TEXT("Image/Mai/Mai_Idle.bmp"),
                1813, 127, 15, 1, true,RGB(17,91,124)
            },
            SpriteSheetInfo{
                "Mai_Foward",
                TEXT("Image/Mai/Mai_FowardMove.bmp"),
                725, 127, 6, 1, true,RGB(17,91,124)
            },
            SpriteSheetInfo{
                "Mai_Back",
                TEXT("Image/Mai/Mai_BackwardMove.bmp"),
                712, 127, 6, 1, true,RGB(17,91,124)
            },
            SpriteSheetInfo{
                "Mai_WeakPunch",
                TEXT("Image/Mai/Mai_WeakPunch.bmp"),
                707, 127, 6, 1, true,RGB(17,91,124)
            },
            SpriteSheetInfo{
                "Mai_WeakKick",
                TEXT("Image/Mai/Mai_WeakKick.bmp"),
                1089, 127, 9, 1, true,RGB(17,91,124)
            },
            SpriteSheetInfo{
                "Mai_StrongPunch",
                TEXT("Image/Mai/Mai_StrongPunch.bmp"),
                716,127, 6, 1, true,RGB(17,91,124)
            },
            SpriteSheetInfo{
                "Mai_StrongKick",
                TEXT("Image/Mai/Mai_StrongKick.bmp"),
                843,127, 7, 1, true,RGB(17,91,124)
            },
            SpriteSheetInfo{
                "Mai_Gaurd",
                TEXT("Image/Mai/Mai_Gaurd.bmp"),
                246, 127, 2, 1, true,RGB(17,91,124)
            },

        }
    };

    character1 = new KOF_Character();
    character1->Init(charinfo, true, false);
    character1->SetPos({200, 300});

    character2 = new KOF_Character();
    character2->Init(charinfo, false, true);
    character2->SetPos({700, 300});
    //

    character1->SetEnemy(character2);
    character2->SetEnemy(character1);
    
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
    background->Update();
    if (character1->GetHealth() <= 0 || character2->GetHealth() <= 0)
    {
        //TODO: Game End, Do Something
        int winnerPlayerIndex = character1->GetHealth() <= 0 ? 2 : 1;
        // switch (winnerPlayerIndex)
        // {
        // case 1:
        //     character1->Update();
        //     break;
        // case 2:
        //     character2->Update();
        //     break;
        // default:
        //     //TODO: Wrong value
        //     break;
        // }
    }
    else
    {
        character1->Update();
        character2->Update();

        character1UI->Update();
        character2UI->Update();
    }

    // Handle Collision
    CheckCollisions();
}

void GameManager::CheckCollisions()
{
    if (RectInRect(character1->GetRcCollision(), character2->GetRcCollision()))
    {
        float pushPower = 1.f;
        float ch1PushAmount = (character1->GetPos().x < character2->GetPos().x ? -1 : 1) * pushPower;
        float ch2PushAmount = (character1->GetPos().x < character2->GetPos().x ? 1 : -1) * pushPower;
        character1->SetPos({character1->GetPos().x + ch1PushAmount, character1->GetPos().y});
        character2->SetPos({character2->GetPos().x + ch2PushAmount, character2->GetPos().y});
    }
    
    
    // Attacker - character2, hit - character1
    if (RectInRect(character2->GetCurrentAttack().hitRect, character1->GetHitRect()))
    {
        character1->GetDamage(character2->GetCurrentAttack().damage, character2->GetCurrentAttack().attackHeightType);
        character1->ResetAttack();
    }
    
    // Attacker - character1, hit - character2
    if (RectInRect(character1->GetCurrentAttack().hitRect, character2->GetHitRect()))
    {
        character2->GetDamage(character1->GetCurrentAttack().damage, character1->GetCurrentAttack().attackHeightType);
        character1->ResetAttack();
    }
}

void GameManager::Render(HDC hdc)
{
    //TODO: Null Check
    background->Render(hdc);

    character1->Render(hdc);
    character2->Render(hdc);
    
    character1UI->Render(hdc);
    character2UI->Render(hdc);
}
