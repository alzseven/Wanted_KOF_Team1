#include "KOF_Character.h"

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
    
    image = new Image[imageCountMax];
    for (int i = 0; i < imageCountMax; ++i)
    {
        if (FAILED(image[i].Init(info.spriteSheet[i].filename,
            info.spriteSheet[i].width, info.spriteSheet[i].height,
            info.spriteSheet[i].maxFrameX, info.spriteSheet[i].maxFrameY,
            info.spriteSheet[i].isTransparent, info.spriteSheet[i].transColor)))
        {
            MessageBox(g_hWnd, info.spriteSheet[i].filename, TEXT("Warning"), MB_OK);
        }
    }
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

    attackRect = RECT{0, 0, 0, 0};
    rcCollision = RECT{0, 0, 50, 100};
#pragma endregion

    this->isMoveable = isMoveable;

    elaspedFrame = 0.0f;
    currAnimaionFrame = 0;

#pragma region SetStates

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
        new KOF_CharacterFiniteStateMachineState*[4];
    states[0] = idleState;
    states[1] = moveState;
    states[2] = attackState;
    states[3] = guardState;
    fsm = new KOF_CharacterFiniteStateMachine();
    fsm->Init(states);

    
    currentMachinState = EFiniteStateMachineState::IDLE;
#pragma endregion
    guardHeight = EAttackHeightType::NONE;
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
    if (isMoveable)
    {
        switch (currentMachinState)
        {
        case EFiniteStateMachineState::IDLE:
            // Check if Attack Key Pressed
                CheckAttack();
            // Check if Move Key Pressed
            if (KeyManager::GetInstance()->IsStayKeyDown(0x44))
            {
                int newState = 1;
                fsm->SetState(newState, 0, static_cast<int>(EMoveType::MOVING_FORWARD));
                currentMachinState = EFiniteStateMachineState::MOVE;
            }
            // Check if Guard
            else if (KeyManager::GetInstance()->IsStayKeyDown(0x41))
            {
                // if enemy close
                //TODO: Get value from config
                if (enemy && GetDistance(enemy->GetPos(), pos) < 200 && enemy->GetCurrentMachinState() == EFiniteStateMachineState::ATTACK)
                {
                    fsm->SetState(3, 0, 2);
                    currentMachinState = EFiniteStateMachineState::GUARD;
                }
                else
                {
                    int newState = 1;
                    fsm->SetState(newState, 0, static_cast<int>(EMoveType::MOVING_BACKWARD));
                    currentMachinState = EFiniteStateMachineState::MOVE;
                }
                // fsm->SetState(static_cast<int>(EFiniteStateMachineState::GUARD), 0);
                // else
            
            }
            break;
        case EFiniteStateMachineState::MOVE:
            CheckAttack();
            if (KeyManager::GetInstance()->IsOnceKeyUp(0x44) || KeyManager::GetInstance()->IsOnceKeyUp(0x41))
            {
                fsm->SetState(0);
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
    }
    else
    {
        if (currentMachinState == EFiniteStateMachineState::IDLE)
        {
            fsm->SetState(1, 0, 1);
            currentMachinState = EFiniteStateMachineState::MOVE;
        }
        // UpdateRect(rcCollision,pos);
    }
    

    //TODO: Match with timer
    float frameSpeed = 20.0f;

    elaspedFrame += frameSpeed;

    if (elaspedFrame < 100.0f) return;

    elaspedFrame = RESET;

    fsm->Update();
}

void KOF_Character::Render(HDC hdc)
{
    // 히트박스 확인용
    // Rectangle(hdc, hitRect.left, hitRect.top, hitRect.right, hitRect.bottom);

    //
    Rectangle(hdc, rcCollision.left, rcCollision.top, rcCollision.right, rcCollision.bottom);
    
    if (fsm) fsm->Render(hdc);
    
    // 히트박스 확인용
    // Rectangle(hdc,currentCombatInfo.hitRect.left, currentCombatInfo.hitRect.top, currentCombatInfo.hitRect.right, currentCombatInfo.hitRect.bottom);
}


void KOF_Character::WeakPunch()
{
    currentCombatInfo.damage = weakPunchDamage;
    
    currentCombatInfo.attackHeightType = EAttackHeightType::UPPER;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    UpdateRect(currentCombatInfo.hitRect, pos);
}

void KOF_Character::StrongPunch()
{
    currentCombatInfo.damage = strongPunchDamage;
    
    currentCombatInfo.attackHeightType = EAttackHeightType::UPPER;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    UpdateRect(currentCombatInfo.hitRect, pos);
}

void KOF_Character::WeakKick()
{
    currentCombatInfo.damage = weakKickDamage;
    
    currentCombatInfo.attackHeightType = EAttackHeightType::LOWER;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    UpdateRect(currentCombatInfo.hitRect, pos);
    
}

void KOF_Character::StrongKick()
{
    currentCombatInfo.damage = strongKickDamage;
    
    currentCombatInfo.attackHeightType = EAttackHeightType::LOWER;
    //TODO: Rename to Attack
    currentCombatInfo.hitRect = RECT{ 100, 0, 120, 100};
    UpdateRect(currentCombatInfo.hitRect, pos);
}

bool KOF_Character::Guard(bool)
{
    return true;
}

void KOF_Character::GetDamage(int damage)
{
    health -= damage;
}

void KOF_Character::GetDamage(int damage, EAttackHeightType attackHeight)
{
    if (guardHeight == EAttackHeightType::NONE)
    {
        health -= damage;
    }
    else
    {
        if (guardHeight == attackHeight)
        {
            // Guard Success
            // TODO: Do something
        }
        else
        {
            health -= damage;
        }
    }
}

void KOF_Character::Move(int dirX)
{
    pos.x = pos.x + moveSpeed * dirX < 0
                ? 0 : pos.x + moveSpeed * dirX > WINSIZE_X - 75
                ? WINSIZE_X - 75 : pos.x + moveSpeed * dirX;
    // pos.x += moveSpeed * dirX;
    UpdateRect(hitRect, pos);
    UpdateRect(rcCollision, pos);
}

void KOF_Character::SetStateToIdle()
{
    fsm->SetState(static_cast<int>(EFiniteStateMachineState::IDLE));
    currentMachinState = EFiniteStateMachineState::IDLE;
}



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