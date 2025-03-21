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
    CharacterInfo kingInfo = CharacterInfo{
        100,
        5.f,
        "King",
        new StateFrameInfo[EKOF_CharacterAction::COUNT_MAX]
        {
            StateFrameInfo{
                EKOF_CharacterAction::IDLE,
                SpriteSheetInfo{
                    "King_Idle",
                    TEXT("Image/King/KingIdle.bmp"),
                    650, 130, 5, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{0, 0, 30, 20},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::MOVE_FORWARD,
                SpriteSheetInfo{
                    "King_Foward",
                    TEXT("Image/King/kingMovingForward.bmp"),
                    650, 130, 5, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{0, 0, 30, 20},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::MOVE_BACK,
                SpriteSheetInfo{
                    "King_Back",
                    TEXT("Image/King/kingMovingBackward.bmp"),
                    650, 130, 5, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{0, 0, 30, 20},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::ATTACK_WEAK_PUNCH,
                SpriteSheetInfo{
                    "King_WeakPunch",
                    TEXT("Image/King/kingWeakPunch.bmp"),
                    650, 130, 5, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{0,0,30,20,},
                5,
                10.f,
                FPOINT{48.f, 75.f},
                FPOINT{100.f, 95.f},
            },
            StateFrameInfo{
                EKOF_CharacterAction::ATTACK_WEAK_KICK,
                SpriteSheetInfo{
                    "King_WeakKick",
                    TEXT("Image/King/KingWeakKick.bmp"),
                    1170, 130, 9, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y, WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y},
                0,
                10.f,
                FPOINT{48, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::ATTACK_STRONG_PUNCH,
                SpriteSheetInfo{
                    "King_StrongPunch",
                    TEXT("Image/King/kingStrongPunch.bmp"),
                    1690, 130, 13, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y, WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::ATTACK_STRONG_KICK,
                SpriteSheetInfo{
                    "King_StrongKick",
                    TEXT("Image/King/KingStrongKick.bmp"),
                    1300, 130, 10, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y, WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::GUARD_STAND,
                SpriteSheetInfo{
                    "King_Guard_Stand",
                    TEXT("Image/King/KingGuard.bmp"),
                    260, 130, 2, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y, WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::GUARD_SIT,
                SpriteSheetInfo{
                    "King_Guard_Sit",
                    TEXT("Image/King/KingSitGuard.bmp"),
                    260, 130, 2, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y, WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
            StateFrameInfo{
                EKOF_CharacterAction::HIT_STUN,
                SpriteSheetInfo{
                    "King_Guard_Stand",
                    TEXT("Image/King/KingGuard.bmp"),
                    260, 130, 2, 1, true,RGB(224, 0, 237)
                },
                RECT{0, 0, 30, 110},
                RECT{WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y, WINSIZE_X + WINSIZE_X, WINSIZE_Y + WINSIZE_Y},
                0,
                10.f,
                FPOINT{30, 75},
                FPOINT{0, 0},
            },
        }
    };


    // CharacterInfo charinfo2 = CharacterInfo{
    //     100,
    //     "King",
    //     new SpriteSheetInfo[10]
    //     {SpriteSheetInfo{
    //         "King_Idle",
    //         TEXT("Image/King/KingIdle.bmp"),
    //         650, 130, 5, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_Foward",
    //         TEXT("Image/King/kingMovingForward.bmp"),
    //         650, 130, 5, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_Back",
    //         TEXT("Image/King/kingMovingBackward.bmp"),
    //         650, 130, 5, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_WeakPunch",
    //         TEXT("Image/King/kingWeakPunch.bmp"),
    //         650, 130, 5, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_WeakKick",
    //         TEXT("Image/King/KingWeakKick.bmp"),
    //         1170, 130, 9, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_StrongPunch",
    //         TEXT("Image/King/kingStrongPunch.bmp"),
    //         1690,130, 13, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_StrongKick",
    //         TEXT("Image/King/KingStrongKick.bmp"),
    //         1300,130, 10, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_Gaurd",
    //         TEXT("Image/King/KingSitGuard.bmp"),
    //         260, 130, 2, 1, true,RGB(224,0,237)
    //     },
    //     SpriteSheetInfo{
    //         "King_Back",
    //         TEXT("Image/King/KingGuard.bmp"),
    //         260, 130, 2, 1, true,RGB(224,0,237)
    //     },
    //
    //         
    //     }
    // };
    // CharacterInfo charinfo = CharacterInfo{
    //     100,
    //     5,
    //     7,
    //     10,
    //     14,
    //     "Mai",
    //     new SpriteSheetInfo[10]{
    //         SpriteSheetInfo{
    //             "Mai_Idle",
    //             TEXT("Image/Mai/Mai_Idle.bmp"),
    //             1736, 129, 14, 1, true,RGB(255,0,255)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_Foward",
    //             TEXT("Image/Mai/Mai_FowardMove.bmp"),
    //             744, 129, 6, 1, true,RGB(255,0,255)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_Back",
    //             TEXT("Image/Mai/Mai_BackwardMove.bmp"),
    //             744, 129, 6, 1, true,RGB(255,0,255)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_WeakPunch",
    //             TEXT("Image/Mai/Mai_WeakPunch.bmp"),
    //             744, 129, 6, 1, true,RGB(255,0,255)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_WeakKick",
    //             TEXT("Image/Mai/Mai_WeakKick.bmp"),
    //             1116, 127, 9, 1, true,RGB(255,0,255)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_StrongPunch",
    //             TEXT("Image/Mai/Mai_StrongPunch.bmp"),
    //             744,129, 6, 1, true,RGB(255,0,255)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_StrongKick",
    //             TEXT("Image/Mai/Mai_StrongKick.bmp"),
    //             868,129, 7, 1, true,RGB(255,0,255)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_Gaurd",
    //             TEXT("Image/Mai/Mai_Gaurd.bmp"),
    //             246, 127, 2, 1, true,RGB(17,91,124)
    //         },
    //         SpriteSheetInfo{
    //             "Mai_Back",
    //             TEXT("Image/Mai/Mai_BackwardMove.bmp"),
    //             744, 129, 6, 1, true,RGB(255,0,255)
    //         },
    //     }
    // };

    character1 = new KOF_Character();
    character1->Init(kingInfo, 1, false);
    character1->SetPos({200, 300});

    character2 = new KOF_Character();
    character2->Init(kingInfo, 2, true);
    character2->SetPos({400, 300});
    //

    character1->SetEnemy(character2);
    character2->SetEnemy(character1);

    // UI Init
    character1UI = new UI;
    character1UI->Init(character1,character2);
  //  character2UI = new UI;
   // character2UI->Init(character2, 100);
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
    //
    // Release and Delete Characters;
    character1->Release();
    delete character1;
 //   character2->Release();
 //   delete character2;
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

    }
    background->Camera(character1->GetPos(), character2->GetPos());
    // Handle Collision
    CheckCollisions();
}

void GameManager::CheckCollisions()
{
    if (RectInRect(character1->GetRcCollision(), character2->GetRcCollision()))
    {
        float ch1PushAmount = (character1->GetPos().x < character2->GetPos().x ? -1 : 1) * character1->GetMoveSpeed();
        float ch2PushAmount = (character1->GetPos().x < character2->GetPos().x ? 1 : -1) * character2->GetMoveSpeed();
        character1->SetPos({character1->GetPos().x + ch1PushAmount, character1->GetPos().y});
        character2->SetPos({character2->GetPos().x + ch2PushAmount, character2->GetPos().y});
    }


    // Attacker - character2, hit - character1
    if (RectInRect(character2->GetCurrentAttack().attackRect, character1->GetHitRect()))
    {
        character1->GetDamage(character2->GetCurrentAttack().damage, character2->GetCurrentAttack().attackHeightType);
        character1->ResetAttack();
    }

    // Attacker - character1, hit - character2
    if (RectInRect(character1->GetCurrentAttack().attackRect, character2->GetHitRect()))
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

    if (character1UI)
        character1UI->Render(hdc);
}
