#include "KOF_Character.h"

#include "Image.h"
#include "KOF_CharacterState.h"
#include "CommonFunction.h"
#include "KOF_CharacterFiniteStateMachine.h"
#include "KOF_CharacterFiniteStateMachineState.h"

void KOF_Character::Init(const CharacterInfo characterInfo, int playerNum, bool isFlip, bool isMoveable)
{
#pragma region SetImages
    int actionCount = static_cast<int>(EKOF_CharacterAction::COUNT_MAX);

    image = new Image[actionCount];

    actionInfo = new StateFrameInfo[actionCount];

    for (int i = 0; i < actionCount; ++i)
    {
        actionInfo[i] = characterInfo.frameInfo[i];
        SpriteSheetInfo currentSpriteSheetInfo = actionInfo[i].spriteSheet;

        if (FAILED(image[i].Init(currentSpriteSheetInfo.filename,
            currentSpriteSheetInfo.width, currentSpriteSheetInfo.height,
            currentSpriteSheetInfo.maxFrameX, currentSpriteSheetInfo.maxFrameY,
            currentSpriteSheetInfo.isTransparent, currentSpriteSheetInfo.transColor)))
        {
            MessageBox(g_hWnd, currentSpriteSheetInfo.filename, TEXT("Warning"), MB_OK);
        }
    }
#pragma endregion
#pragma region SetData
    pos = {0.0f, 0.0f};
    moveSpeed = characterInfo.moveSpeed;

    maxHealth = health = characterInfo.maxHealth;
    characterName = characterInfo.characterName;
    this->isFlip = isFlip;

    //TODO: 
    hitRect = RECT{0, 0, 30, 110};
    attackRect = RECT{0, 0, 0, 0};
    rcCollision = RECT{0, 0, 30, 110};
#pragma endregion

    this->isMoveable = isMoveable;

    elaspedFrame = 0.0f;
    // currAnimaionFrame = 0;

#pragma region SetStates

    idleState = new KOF_CharacterStateIdle();
    idleState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EKOF_CharacterAction::IDLE)]
        },
        new StateFrameInfo[]{
            actionInfo[static_cast<int>(EKOF_CharacterAction::IDLE)]
        }
    );

    moveState = new KOF_CharacterStateMove();
    moveState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EKOF_CharacterAction::MOVE_FORWARD)],
            image[static_cast<int>(EKOF_CharacterAction::MOVE_BACK)],
        },
        new StateFrameInfo[]
        {
            actionInfo[static_cast<int>(EKOF_CharacterAction::MOVE_FORWARD)],
            actionInfo[static_cast<int>(EKOF_CharacterAction::MOVE_BACK)],
        }
    );
    attackState = new KOF_CharacterStateAttack();
    attackState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_PUNCH)],
            image[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_KICK)],
            image[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_PUNCH)],
            image[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_KICK)],
        },
        new StateFrameInfo[]
        {
            actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_PUNCH)],
            actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_KICK)],
            actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_PUNCH)],
            actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_KICK)],
        }
    );
    guardState = new KOF_CharacterStateGuard();
    guardState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EKOF_CharacterAction::GUARD_STAND)],
            image[static_cast<int>(EKOF_CharacterAction::GUARD_SIT)],
        },
        new StateFrameInfo[]
        {
            actionInfo[static_cast<int>(EKOF_CharacterAction::GUARD_STAND)],
            actionInfo[static_cast<int>(EKOF_CharacterAction::GUARD_SIT)],
        }
    );
    hitStunState = new KOF_CharacterStateHitStun();
    hitStunState->Init(
        this,
        new Image[]
        {
            image[static_cast<int>(EKOF_CharacterAction::HIT_STUN)],
        },
        new StateFrameInfo[]
        {
            actionInfo[static_cast<int>(EKOF_CharacterAction::HIT_STUN)],
        }
    );

    states = new KOF_CharacterFiniteStateMachineState*[static_cast<int>(EFiniteStateMachineState::COUNT_MAX)];
    states[static_cast<int>(EFiniteStateMachineState::IDLE)] = idleState;
    states[static_cast<int>(EFiniteStateMachineState::MOVE)] = moveState;
    states[static_cast<int>(EFiniteStateMachineState::ATTACK)] = attackState;
    states[static_cast<int>(EFiniteStateMachineState::GUARD)] = guardState;
    states[static_cast<int>(EFiniteStateMachineState::HITSTUN)] = hitStunState;
    fsm = new KOF_CharacterFiniteStateMachine();
    fsm->Init(states);
    ChangeState(EFiniteStateMachineState::IDLE, actionInfo[static_cast<int>(EKOF_CharacterAction::IDLE)]);

#pragma endregion
    guardHeight = EAttackHeightType::NONE;
    this->playerNum = playerNum;

    switch (this->playerNum)
    {
    case 1:
        // isMoveable = true;
        MOVEFOWARD = 0x44;
        MOVEBACKWARD = 0x41;
        SIT_DOWN = 0x53;
        ATTACK_WEAK_PUNCH = 0x47;
        ATTACK_STRONG_PUNCH = 0x54;
        ATTACK_WEAK_KICK = 0x48;
        ATTACK_STRONG_KICK = 0x59;

        break;
    case 2:
        // isMoveable = true;
        MOVEFOWARD = 0x4A;
        MOVEBACKWARD = 0x4C;
        SIT_DOWN = 0x6C;
        ATTACK_WEAK_PUNCH = 0x65;
        ATTACK_STRONG_PUNCH = 0x68;
        ATTACK_WEAK_KICK = 0x66;
        ATTACK_STRONG_KICK = 0x69;

        break;
    }
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
            if (KeyManager::GetInstance()->IsStayKeyDown(MOVEFOWARD))
            {
                ChangeState(EFiniteStateMachineState::MOVE,
                            actionInfo[static_cast<int>(EKOF_CharacterAction::MOVE_FORWARD)], 0,
                            static_cast<int>(EMoveType::MOVING_FORWARD));
            }
            // Check if Guard
            else if (KeyManager::GetInstance()->IsStayKeyDown(MOVEBACKWARD))
            {
                // if enemy close
                if (enemy && GetDistance(enemy->GetPos(), pos) < GUARD_DETECTION_DISTANCE && enemy->
                    GetCurrentMachinState() == EFiniteStateMachineState::ATTACK)
                {
                    if (KeyManager::GetInstance()->IsStayKeyDown(SIT_DOWN))
                    {
                        ChangeState(EFiniteStateMachineState::GUARD,
                                    actionInfo[static_cast<int>(EKOF_CharacterAction::GUARD_SIT)], 0,
                                    static_cast<int>(EAttackHeightType::LOWER));
                    }
                    else
                    {
                        ChangeState(EFiniteStateMachineState::GUARD,
                                    actionInfo[static_cast<int>(EKOF_CharacterAction::GUARD_STAND)], 0,
                                    static_cast<int>(EAttackHeightType::UPPER));
                    }
                }
                else
                {
                    ChangeState(EFiniteStateMachineState::MOVE,
                                actionInfo[static_cast<int>(EKOF_CharacterAction::MOVE_BACK)], 0,
                                static_cast<int>(EMoveType::MOVING_BACKWARD));
                }
            }
            break;
        case EFiniteStateMachineState::MOVE:
            CheckAttack();
            if (KeyManager::GetInstance()->IsOnceKeyUp(MOVEFOWARD) || KeyManager::GetInstance()->IsOnceKeyUp(
                MOVEBACKWARD))
            {
                ChangeState(EFiniteStateMachineState::IDLE,
                            actionInfo[static_cast<int>(EKOF_CharacterAction::IDLE)]);
            }
            break;
        case EFiniteStateMachineState::ATTACK:
            // exit on animation ends
            break;
        case EFiniteStateMachineState::GUARD:
            if (KeyManager::GetInstance()->IsOnceKeyUp(MOVEBACKWARD))
            {
                ChangeState(EFiniteStateMachineState::IDLE,
                            actionInfo[static_cast<int>(EKOF_CharacterAction::IDLE)]);
            }
            break;
        case EFiniteStateMachineState::HITSTUN:
            // exit on animation ends
            break;
        default:
            //TODO : Something Wrong
            break;
        }
    }
    else
    {
        // Test codes for unmoving character
        if (currentMachinState == EFiniteStateMachineState::IDLE)
        {
            ChangeState(EFiniteStateMachineState::ATTACK,
                        actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_PUNCH)], 0,
                        static_cast<int>(EAttackType::WEAK_PUNCH));
        }
    }

    elaspedFrame += TIMER_TICK;

    if (elaspedFrame >= FRAME_TICK)
    {
        elaspedFrame -= FRAME_TICK;

        fsm->Update();
    }
}

void KOF_Character::Render(HDC hdc)
{
    // // 히트박스 확인용
    // Rectangle(hdc, hitRect.left, hitRect.top, hitRect.right, hitRect.bottom);
    //
    // // 히트박스 확인용
    // Rectangle(hdc, currentCombatInfo.attackRect.left, currentCombatInfo.attackRect.top,
    //           currentCombatInfo.attackRect.right, currentCombatInfo.attackRect.bottom);
    //
    if (fsm) fsm->Render(hdc,isFlip);

    
}

void KOF_Character::Attack(EAttackType attackType)
{
    StateFrameInfo currentActionInfo;
    switch (attackType)
    {
    case EAttackType::WEAK_PUNCH:
        currentActionInfo = actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_PUNCH)];
        currentCombatInfo.attackHeightType = EAttackHeightType::UPPER;
        break;
    case EAttackType::WEAK_KICK:
        currentActionInfo = actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_KICK)];
        currentCombatInfo.attackHeightType = EAttackHeightType::LOWER;
        break;
    case EAttackType::STRONG_PUNCH:
        currentActionInfo = actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_PUNCH)];
        currentCombatInfo.attackHeightType = EAttackHeightType::UPPER;
        break;
    case EAttackType::STRONG_KICK:
        currentActionInfo = actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_KICK)];
        currentCombatInfo.attackHeightType = EAttackHeightType::LOWER;
        break;
    default:
        //
        break;
    }

    currentCombatInfo.damage = currentActionInfo.damage;
    currentCombatInfo.attackRect = currentActionInfo.rectAttack;
    // UpdateRect(currentCombatInfo.attackRect, po)
    UpdateRect(currentCombatInfo.attackRect, {pos.x + currentActionInfo.rectAttackOffset.x * (isFlip ? -1 : 1),  pos.y + currentActionInfo.rectAttackOffset.y});
    // UpdateRect(currentCombatInfo.attackRect, {, });
}


void KOF_Character::ResetAttack()
{
    currentCombatInfo.damage = 0;
    UpdateRect(currentCombatInfo.attackRect, {0, 0});
    currentCombatInfo.attackHeightType = EAttackHeightType::NONE;
}

void KOF_Character::GetDamage(int damage, EAttackHeightType attackHeight)
{
    if (guardHeight == EAttackHeightType::NONE)
    {
        health -= damage;
        ChangeState(EFiniteStateMachineState::HITSTUN,
                            actionInfo[static_cast<int>(EKOF_CharacterAction::HIT_STUN)], 0,
                            damage / 3);
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
            ChangeState(EFiniteStateMachineState::HITSTUN,
                            actionInfo[static_cast<int>(EKOF_CharacterAction::HIT_STUN)], 0,
                            damage / 3);
        }
    }
}

void KOF_Character::Move(EMoveType moveType)
{
    int dirX = moveType != EMoveType::COUNT_MAX ? moveType == EMoveType::MOVING_FORWARD ? 1 : -1 : 0;
    dirX *= isFlip ? -1 : 1;
    pos.x = pos.x + moveSpeed * dirX < 0
                //TODO:
                ? 0
                : pos.x + moveSpeed * dirX > WINSIZE_X - 75
                ? WINSIZE_X - 75
                : pos.x + moveSpeed * dirX;
    int actionIndex = moveType != EMoveType::COUNT_MAX ? moveType == EMoveType::MOVING_FORWARD ? static_cast<int>(EKOF_CharacterAction::MOVE_FORWARD) : static_cast<int>(EKOF_CharacterAction::MOVE_BACK) : 0;
    StateFrameInfo currentActionInfo = actionInfo[actionIndex];
    hitRect = currentActionInfo.rectHit;
    rcCollision = hitRect;
    UpdateRect(hitRect, pos);
    UpdateRect(rcCollision, pos);
    // UpdateRect(hitRect, {pos.x + currentActionInfo.rectHitOffset.x * (isFlip ? -1 : 1) , pos.y + currentActionInfo.rectHitOffset.y});
    // UpdateRect(rcCollision, {pos.x + currentActionInfo.rectHitOffset.x * (isFlip ? -1 : 1) ,pos.y + currentActionInfo.rectHitOffset.y});
}

void KOF_Character::SetPos(FPOINT pos)
{
    this->pos = pos;
    
    StateFrameInfo currentActionInfo = actionInfo[static_cast<int>(EKOF_CharacterAction::IDLE)];
    hitRect = currentActionInfo.rectHit;
    rcCollision = hitRect;
    UpdateRect(hitRect, pos);
    UpdateRect(rcCollision, pos);
    // UpdateRect(hitRect, {pos.x + currentActionInfo.rectHitOffset.x * (isFlip ? -1 : 1) , pos.y + currentActionInfo.rectHitOffset.y});
    // UpdateRect(rcCollision, {pos.x + currentActionInfo.rectHitOffset.x * (isFlip ? -1 : 1) ,pos.y + currentActionInfo.rectHitOffset.y});
}

void KOF_Character::SetStateToIdle()
{
    ChangeState(EFiniteStateMachineState::IDLE, actionInfo[static_cast<int>(EKOF_CharacterAction::IDLE)]);
}

void KOF_Character::CheckAttack()
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_WEAK_PUNCH))
    {
        ChangeState(EFiniteStateMachineState::ATTACK,
                    actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_PUNCH)], 0,
                    static_cast<int>(EAttackType::WEAK_PUNCH));
    }
    else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_WEAK_KICK))
    {
        ChangeState(EFiniteStateMachineState::ATTACK,
                    actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_WEAK_KICK)], 0,
                    static_cast<int>(EAttackType::WEAK_KICK));
    }
    // J key : 강펀치
    else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_STRONG_PUNCH))
    {
        ChangeState(EFiniteStateMachineState::ATTACK,
                    actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_PUNCH)], 0,
                    static_cast<int>(EAttackType::STRONG_PUNCH));
    }
    // K key : 강발
    else if (KeyManager::GetInstance()->IsOnceKeyDown(ATTACK_STRONG_KICK))
    {
        ChangeState(EFiniteStateMachineState::ATTACK,
                    actionInfo[static_cast<int>(EKOF_CharacterAction::ATTACK_STRONG_KICK)], 0,
                    static_cast<int>(EAttackType::STRONG_KICK));
    }
}

void KOF_Character::ChangeState(EFiniteStateMachineState newState, const StateFrameInfo& newActionInfo,
                                int exitStateParam, int enterStateParam)
{
    hitRect = newActionInfo.rectHit;
    rcCollision = hitRect;
    currentCombatInfo.attackRect = newActionInfo.rectAttack;
    ResetAttack();
    fsm->SetState(static_cast<int>(newState), exitStateParam, enterStateParam);
    currentMachinState = newState;
    UpdateRect(hitRect, pos);
    UpdateRect(rcCollision, pos);
    // UpdateRect(hitRect, {pos.x + (newActionInfo.rectHitOffset.x * (isFlip ? -1 : 1)) , pos.y + newActionInfo.rectHitOffset.y});
    // int a = 0;
    // UpdateRect(rcCollision, {pos.x + (newActionInfo.rectHitOffset.x * (isFlip ? -1 : 1)) , pos.y + newActionInfo.rectHitOffset.y});
}
