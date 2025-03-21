#include "KOF_CharacterFiniteStateMachineState.h"

#include "Image.h"
#include "KOF_Character.h"
#include "KOF_CharacterState.h"

#pragma region KOF_CharacterFiniteStateMachineState

void KOF_CharacterFiniteStateMachineState::Init(KOF_Character* character, Image* stateImage, StateFrameInfo* actionFrameInfo)
{
    this->character = character;
    this->stateImage = stateImage;
    this->actionFrameInfo = actionFrameInfo;
    
    currentFrameIndex = 0;
}

void KOF_CharacterFiniteStateMachineState::Release()
{
    if (character)
    {
        delete character;
        character = nullptr;
    }

    if (actionFrameInfo)
    {
        delete actionFrameInfo;
        actionFrameInfo = nullptr;
    }
}

#pragma endregion

#pragma region KOF_CharacterStateIdle

void KOF_CharacterStateIdle::Init(KOF_Character* character, Image* stateImage, StateFrameInfo* actionFrameInfo)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, actionFrameInfo);
}

void KOF_CharacterStateIdle::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    maxFrameCount = actionFrameInfo[stateParam].spriteSheet.maxFrameX - 1;
}

void KOF_CharacterStateIdle::ExitState(int stateParam) { }

void KOF_CharacterStateIdle::Update()
{
    currentFrameIndex = currentFrameIndex + 1 > maxFrameCount ? 0 : currentFrameIndex + 1;
}

void KOF_CharacterStateIdle::Release()
{
    KOF_CharacterFiniteStateMachineState::Release();
}

void KOF_CharacterStateIdle::Render(HDC hdc)
{
    stateImage->Render(hdc, character->GetPos().x, character->GetPos().y, currentFrameIndex);
}

#pragma endregion

#pragma region KOF_CharacterStateMove

void KOF_CharacterStateMove::Init(KOF_Character* character, Image* stateImage, StateFrameInfo* actionFrameInfo)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, actionFrameInfo);
}

void KOF_CharacterStateMove::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    //TODO: check cast available
    moveType = static_cast<EMoveType>(stateParam);
    maxFrameCount = actionFrameInfo[static_cast<int>(moveType)].spriteSheet.maxFrameX - 1;
}

void KOF_CharacterStateMove::ExitState(int stateParam) { }

void KOF_CharacterStateMove::Update()
{
    character->Move(moveType);
    currentFrameIndex = currentFrameIndex + 1 > maxFrameCount ? 0 : currentFrameIndex + 1;
}

void KOF_CharacterStateMove::Render(HDC hdc)
{
    stateImage[static_cast<int>(moveType)].Render(hdc, character->GetPos().x, character->GetPos().y, currentFrameIndex);
}

void KOF_CharacterStateMove::Release()
{
    KOF_CharacterFiniteStateMachineState::Release();
}

#pragma endregion

//---

#pragma region KOF_CharacterStateAttack

void KOF_CharacterStateAttack::Init(KOF_Character* character, Image* stateImage, StateFrameInfo* actionFrameInfo)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, actionFrameInfo);
}

void KOF_CharacterStateAttack::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    attackType = static_cast<EAttackType>(stateParam);
    maxFrameCount = actionFrameInfo[static_cast<int>(attackType)].spriteSheet.maxFrameX - 1;
    // actionFrameInfo[attackType]
    character->Attack(attackType);
    // switch (attackType)
    // {
    // case EAttackType::WEAK_PUNCH:
    //     character->WeakPunch();
    //     break;
    // case EAttackType::WEAK_KICK:
    //     character->WeakKick();
    //     break;
    // case EAttackType::STRONG_PUNCH:
    //     character->StrongPunch();
    //     break;
    // case EAttackType::STRONG_KICK:
    //     character->StrongKick();
    //     break;
    // default:
    //     break;
    // }
}

void KOF_CharacterStateAttack::ExitState(int stateParam)
{
    character->ResetAttack();
}

void KOF_CharacterStateAttack::Update()
{
    currentFrameIndex = currentFrameIndex + 1;
    if (currentFrameIndex > maxFrameCount) character->SetStateToIdle();
}

void KOF_CharacterStateAttack::Render(HDC hdc)
{
    // KOF_CharacterFiniteStateMachineState::Render(hdc);
    stateImage[static_cast<int>(attackType)].Render(hdc, character->GetPos().x, character->GetPos().y, currentFrameIndex);
}
void KOF_CharacterStateAttack::Release()
{
    KOF_CharacterFiniteStateMachineState::Release();
}

#pragma endregion

// ---

#pragma region KOF_CharacterStateGuard

void KOF_CharacterStateGuard::Init(KOF_Character* character, Image* stateImage, StateFrameInfo* actionFrameInfo)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, actionFrameInfo);
}

void KOF_CharacterStateGuard::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    guardHeightType = static_cast<EAttackHeightType>(stateParam);
    switch (guardHeightType)
    {
    case EAttackHeightType::UPPER:
        character->SetGuardHeight(EAttackHeightType::UPPER);
        break;
    case EAttackHeightType::LOWER:
        character->SetGuardHeight(EAttackHeightType::LOWER);
        break;
    default:
        //TODO: Wrong cases
        break;
    }
}

void KOF_CharacterStateGuard::ExitState(int stateParam)
{
    character->SetGuardHeight(EAttackHeightType::NONE);
}

void KOF_CharacterStateGuard::Update()
{
    currentFrameIndex = currentFrameIndex + 1;
    if (currentFrameIndex > maxFrameCount) currentFrameIndex = maxFrameCount;
}

void KOF_CharacterStateGuard::Render(HDC hdc)
{
    stateImage->Render(hdc, character->GetPos().x, character->GetPos().y, currentFrameIndex);
}

void KOF_CharacterStateGuard::Release()
{
    KOF_CharacterFiniteStateMachineState::Release();
}

#pragma endregion

// ---

void KOF_CharacterStateHitStun::Init(KOF_Character* character, Image* stateImage, StateFrameInfo* actionFrameInfo)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, actionFrameInfo);
}

void KOF_CharacterStateHitStun::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    stunFrame = stateParam;
}

void KOF_CharacterStateHitStun::ExitState(int stateParam)
{
}

void KOF_CharacterStateHitStun::Update()
{
    currentFrameIndex = currentFrameIndex + 1;
    if (currentFrameIndex > stunFrame) character->SetStateToIdle();
}

void KOF_CharacterStateHitStun::Render(HDC hdc)
{
    // KOF_CharacterFiniteStateMachineState::Render(hdc);
    stateImage->Render(hdc, character->GetPos().x, character->GetPos().y, currentFrameIndex >= maxFrameCount ? maxFrameCount : currentFrameIndex);
}

void KOF_CharacterStateHitStun::Release()
{
    KOF_CharacterFiniteStateMachineState::Release();
}
