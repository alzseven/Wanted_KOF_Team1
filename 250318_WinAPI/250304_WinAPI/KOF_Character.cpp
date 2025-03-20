#include "KOF_Character.h"

// #include <assert.h>

#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"
#include "KOF_CharacterFiniteStateMachine.h"
#include "KOF_CharacterFiniteStateMachineState.h"

void KOF_Character::Init(const CharacterInfo info, bool isMoveable, bool isFlip)
{
#pragma region SetImages
    //TODO:
    int imageCountMax = static_cast<int>(EFiniteStateMachineState::COUNT_MAX);

    // assert((sizeof(info.spriteSheet) / sizeof(*info.spriteSheet)) == imageCountMax);
    
    image = new Image[imageCountMax - 1];
    for (int i = 0; i < imageCountMax - 1; ++i)
    {
        if (FAILED(image[i].Init(info.spriteSheet[i].filename,
            info.spriteSheet[i].width, info.spriteSheet[i].height,
            info.spriteSheet[i].maxFrameX, info.spriteSheet[i].maxFrameY,
            info.spriteSheet[i].isTransparent, info.spriteSheet[i].transColor)))
        {
            MessageBox(g_hWnd, info.spriteSheet[i].filename, TEXT("Warning"), MB_OK);
        }
    }
    
    
    // image = new Image[5];
    // for (int i = 0; i < 5; i++)
    // {
    //     if (FAILED(image[i].Init(info.spriteSheet[i].filename,
    //         info.spriteSheet[i].width, info.spriteSheet[i].height,
    //         info.spriteSheet[i].maxFrameX, info.spriteSheet[i].maxFrameY,
    //         info.spriteSheet[i].isTransparent, info.spriteSheet[i].transColor)))
    //     {
    //         MessageBox(g_hWnd, info.spriteSheet[i].filename, TEXT("Warning"), MB_OK);
    //     }
    // }
#pragma endregion
#pragma region SetData
    pos = {0.0f, 0.0f};
    moveSpeed = 5.0f;

    health = info.health;
    weakPunchDamage = info.weakPunchDamage;
    weakKickDamage = info.weakKickDamage;
    strongPunchDamage = info.strongPunchDamage;
    strongKickDamage = info.strongKickDamage;
    characterName = info.characterName;
    this->isFlip = isFlip;

    //TODO: 
    hitRect = RECT{0, 0, 50, 100};
    // hitRect = RECT{ 0, 0, info.spriteSheet[0].width/info.spriteSheet[0].maxFrameX, info.spriteSheet[0].height/info.spriteSheet[0].maxFrameY};
    attackRect = RECT{0, 0, 0, 0};
#pragma endregion

    this->isMoveable = isMoveable;
    elaspedFrame = 0.0f;
    currAnimaionFrame = 0;

#pragma region SetStates
    //TODO:
    isWeakPunching = false;

    idleState = new KOF_CharacterStateIdle();
    idleState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EFiniteStateMachineState::IDLE)]
        },
        info.spriteSheet[static_cast<int>(EFiniteStateMachineState::IDLE)].maxFrameX
    );

    //TODO: Add more than one images
    moveState = new KOF_CharacterStateMove();
    moveState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EFiniteStateMachineState::MOVE) + static_cast<int>(EMoveType::MOVING_FORWARD)],
            image[static_cast<int>(EFiniteStateMachineState::MOVE) + static_cast<int>(EMoveType::MOVING_BACKWARD)]
        },
        info.spriteSheet[static_cast<int>(EFiniteStateMachineState::MOVE)].maxFrameX
    );
    attackState = new KOF_CharacterStateAttack();
    attackState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EFiniteStateMachineState::ATTACK)+ static_cast<int>(EAttackType::WEAK_PUNCH)],
            image[static_cast<int>(EFiniteStateMachineState::ATTACK)+ static_cast<int>(EAttackType::WEAK_KICK)],
            image[static_cast<int>(EFiniteStateMachineState::ATTACK)+ static_cast<int>(EAttackType::STRONG_PUNCH)],
            image[static_cast<int>(EFiniteStateMachineState::ATTACK)+ static_cast<int>(EAttackType::STRONG_KICK)],
        },
        info.spriteSheet[static_cast<int>(EFiniteStateMachineState::ATTACK)].maxFrameX
    );
    guardState = new KOF_CharacterStateGuard();
    guardState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EFiniteStateMachineState::GUARD)]
        },
        info.spriteSheet[static_cast<int>(EFiniteStateMachineState::GUARD)].maxFrameX
    );

    states =
        new KOF_CharacterFiniteStateMachineState*[static_cast<int>(EFiniteStateMachineState::COUNT_MAX) -
            (static_cast<int>(EMoveType::COUNT_MAX)) - (static_cast<int>(EAttackType::COUNT_MAX))];
    states[static_cast<int>(EFiniteStateMachineState::IDLE)] = idleState;
    states[static_cast<int>(EFiniteStateMachineState::MOVE) -
        static_cast<int>(EFiniteStateMachineState::IDLE)] = moveState;
    states[static_cast<int>(EFiniteStateMachineState::ATTACK) -
        static_cast<int>(EFiniteStateMachineState::MOVE)] = attackState;
    states[static_cast<int>(EFiniteStateMachineState::GUARD) -
        static_cast<int>(EFiniteStateMachineState::ATTACK)] = guardState;
    fsm = new KOF_CharacterFiniteStateMachine();
    fsm->Init(states);

    
    currentMachinState = EFiniteStateMachineState::IDLE;
#pragma endregion
}

void KOF_Character::Release()
{
    delete idleState;
    delete moveState;
    delete attackState;
    delete guardState;
    delete[] states;
    delete[] image;
}

void KOF_Character::Update()
{
    

    switch (currentMachinState)
    {
    case EFiniteStateMachineState::IDLE:
        // Check if Attack Key Pressed
        CheckAttack();
        // Check if Move Key Pressed
        if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
        {
            int newState = static_cast<int>(EFiniteStateMachineState::MOVE);
            fsm->SetState(newState, 0, static_cast<int>(EMoveType::MOVING_FORWARD));
            currentMachinState = EFiniteStateMachineState::MOVE;
        }
        // Check if Guard
        else if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
        {
            // if enemy close
            // fsm->SetState(static_cast<int>(EFiniteStateMachineState::GUARD));
            // else
            int newState = static_cast<int>(EFiniteStateMachineState::MOVE);
            fsm->SetState(newState, 0, static_cast<int>(EMoveType::MOVING_BACKWARD));
            currentMachinState = EFiniteStateMachineState::MOVE;
        }
        break;
    case EFiniteStateMachineState::MOVE:
        CheckAttack();
        if (KeyManager::GetInstance()->IsOnceKeyUp(0x44) || KeyManager::GetInstance()->IsOnceKeyUp(0x41))
        {
            fsm->SetState(static_cast<int>(EFiniteStateMachineState::IDLE));
            currentMachinState = EFiniteStateMachineState::IDLE;
        }
        break;
    case EFiniteStateMachineState::ATTACK:
        // exit on animation ends
        break;
    case EFiniteStateMachineState::GUARD:
        if (KeyManager::GetInstance()->IsOnceKeyUp(0x41))
        {
            fsm->SetState(static_cast<int>(EFiniteStateMachineState::IDLE));
            currentMachinState = EFiniteStateMachineState::IDLE;
        }
        break;
    default:
        //TODO : Something Wrong
        break;
    }

    //TODO: Match with timer
    float frameSpeed = 20.0f;

    elaspedFrame += frameSpeed;

    if (elaspedFrame < 100.0f) return;

    elaspedFrame = RESET;

    fsm->Update();
    
    // float frameSpeed = 20.0f;
    //
    // elaspedFrame += frameSpeed;

    // if (elaspedFrame >= 100.0f)
    // {
    //     currentFrameIndex++;
    //
    //     elaspedFrame = RESET;
    // }
    //
    // if (currentFrameIndex >= 15 && currentActionState == static_cast<int>(State::Idle))
    // {
    //     currentFrameIndex = RESET;
    // }
    //
    // switch (currentActionState)
    // {
    // case static_cast<int>(State::StrongPunch):
    //     if (currentFrameIndex >= 6)
    //     {
    //         currentFrameIndex = RESET;
    //         currentActionState = static_cast<int>(State::Idle);
    //     }
    //     break;
    // case static_cast<int>(State::StrongKick):
    //     if (currentFrameIndex >= 7)
    //     {
    //         currentFrameIndex = RESET;
    //         currentActionState = static_cast<int>(State::Idle);
    //     }
    //     break;
    // }
    //
    //
    // // D key : 앞이동
    // if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))
    // {
    //     currentFrameIndex = RESET;
    //     currentActionState = static_cast<int>(State::MovingFoward);
    // }
    // if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
    // {
    //     pos.x += 2.0f * (frameSpeed / moveSpeed);
    //     if (currentFrameIndex >= 6)
    //     {
    //         currentFrameIndex = RESET;
    //     }
    // }
    // if (KeyManager::GetInstance()->IsOnceKeyUp(0x44))
    // {
    //     currentFrameIndex = RESET;
    //     currentActionState = static_cast<int>(State::Idle);
    // }
    //
    //
    // // A Key : 뒤로 이동
    // if (KeyManager::GetInstance()->IsOnceKeyDown(0x41))
    // {
    //     currentFrameIndex = 0;
    //     currentActionState = static_cast<int>(State::MovingBack);
    // }
    // if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
    // {
    //     pos.x -= 2.0f * (frameSpeed / moveSpeed);
    //
    //     if (currentFrameIndex >= 6)
    //     {
    //         currentFrameIndex = RESET;
    //     }
    // }
    // if (KeyManager::GetInstance()->IsOnceKeyUp(0x41))
    // {
    //     currentFrameIndex = RESET;
    //     currentActionState = static_cast<int>(State::Idle);
    // }
    //
    // // J key : 강펀치
    // if (KeyManager::GetInstance()->IsOnceKeyDown(0x4A))
    // {
    //     StrongPunch();
    // }
    //
    // // K key : 강발
    // if (KeyManager::GetInstance()->IsOnceKeyDown(0x4B))
    // {
    //     StrongKick();
    // }
}

void KOF_Character::Render(HDC hdc)
{
    // 히트박스 확인용
    //if (currentActionState == static_cast<int>(State::Idle))
    RenderRect(hdc, pos.x + 27, pos.y, 38, 94);

    fsm->Render(hdc);
    // if (image)
    //     image[currentActionState].Render(hdc, pos.x, pos.y, currentFrameIndex, isFlip);

    // 히트박스 확인용
    if (currentActionState == static_cast<int>(State::StrongKick))
        //RenderRect(hdc, pos.x + 107, pos.y, 25, 94);
        RenderRect(hdc, (int)(pos.x + 100), (int)(pos.y), 20, 100);


    if (currentActionState == static_cast<int>(State::StrongPunch))
        //RenderRect(hdc, pos.x + 97, pos.y, 20, 94);
        RenderRect(hdc, (int)(pos.x + 100), (int)(pos.y), 20, 100);
}


void KOF_Character::WeakPunch()
{
    currentCombatInfo.damage = weakPunchDamage;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    currentCombatInfo.attackHeightType = EAttackHeightType::UPPER;
    UpdateRect(currentCombatInfo.hitRect, pos);
    
    // int newState = static_cast<int>(EFiniteStateMachineState::ATTACK) - static_cast<int>(
    //     EFiniteStateMachineState::MOVE);
    // fsm->SetState(newState, 0, static_cast<int>(EAttackType::WEAK_PUNCH));
    //
}

void KOF_Character::StrongPunch()
{
    currentCombatInfo.damage = strongPunchDamage;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    currentCombatInfo.attackHeightType = EAttackHeightType::UPPER;
    UpdateRect(currentCombatInfo.hitRect, pos);
    
    // int newState = static_cast<int>(EFiniteStateMachineState::ATTACK) + 1 - static_cast<int>(
    //     EAttackType::COUNT_MAX);
    // fsm->SetState(newState, 0, static_cast<int>(EAttackType::STRONG_PUNCH));
}

void KOF_Character::WeakKick()
{
    currentCombatInfo.damage = weakKickDamage;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    currentCombatInfo.attackHeightType = EAttackHeightType::LOWER;
    UpdateRect(currentCombatInfo.hitRect, pos);
    
}

void KOF_Character::StrongKick()
{
    currentCombatInfo.damage = strongKickDamage;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    currentCombatInfo.attackHeightType = EAttackHeightType::LOWER;
    UpdateRect(currentCombatInfo.hitRect, pos);
    
    
    // if (currentActionState == static_cast<int>(State::StrongKick)) return;
    // currentFrameIndex = RESET;
    // currentActionState = static_cast<int>(State::StrongKick);
    // currentCombatInfo.damage = strongKickDamage;
    // currentCombatInfo.hitRect = RECT{(int)(pos.x + 100), (int)(pos.y), (int)(pos.x + 100) + 20, (int)pos.y + 100};
    //
    // elaspedFrame = RESET;
}

bool KOF_Character::Guard(bool)
{
    return true;
}

void KOF_Character::GetDamage(int damage)
{
    health -= damage;
}

//TODO:
void KOF_Character::Move()
{
    pos.x += moveSpeed;
}

void KOF_Character::Move(int dirX)
{
    pos.x += moveSpeed * dirX;
    UpdateRect(hitRect, pos);
}

void KOF_Character::SetStateToIdle()
{
    fsm->SetState(static_cast<int>(EFiniteStateMachineState::IDLE));
    currentMachinState = EFiniteStateMachineState::IDLE;
}

int KOF_Character::GetHealth() { return health; }


RECT KOF_Character::GetHitRect() { return hitRect; }

RECT KOF_Character::GetAttackRect() { return attackRect; }

// void KOF_Character::LoopFrame(int frameIndexMax)
// {
//     currentFrameIndex = currentFrameIndex > frameIndexMax ? RESET : currentFrameIndex++;
// }

void KOF_Character::CheckAttack()
{
    // J key : 강펀치
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x4A))
    {
        // StrongPunch();
        int newState = static_cast<int>(EFiniteStateMachineState::ATTACK) - static_cast<int>(EFiniteStateMachineState::MOVE);
        fsm->SetState(newState, 0, static_cast<int>(EAttackType::STRONG_PUNCH));
        currentMachinState = EFiniteStateMachineState::ATTACK;
    }
    // K key : 강발
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x4B))
    {
        // StrongKick();
        int newState = static_cast<int>(EFiniteStateMachineState::ATTACK) - static_cast<int>(EFiniteStateMachineState::MOVE);
        fsm->SetState(newState, 0, static_cast<int>(EAttackType::STRONG_KICK));
        currentMachinState = EFiniteStateMachineState::ATTACK;
    }
}