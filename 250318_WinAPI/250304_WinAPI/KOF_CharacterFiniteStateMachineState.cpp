#include "KOF_CharacterFiniteStateMachineState.h"

#include "Image.h"
#include "KOF_Character.h"
#include "KOF_CharacterState.h"


void KOF_CharacterFiniteStateMachineState::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
{
    this->character = character;
    this->stateImage = stateImage;
    this->maxFrameCount = maxFrameCount - 1;

    currentFrameIndex = 0;
}

// void KOF_CharacterFiniteStateMachineState::EnterState(int stateParam)
// {
// }
//
// void KOF_CharacterFiniteStateMachineState::ExitState(int stateParam)
// {
// }
//
// void KOF_CharacterFiniteStateMachineState::Update()
// {
// }

void KOF_CharacterFiniteStateMachineState::Release()
{
    if (character)
        delete character;
    if (stateImage)
        delete stateImage;
}

void KOF_CharacterStateIdle::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, maxFrameCount);
}


// --- 

// void KOF_CharacterStateIdle::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
// {
//     currentFrameIndex = 0;
//     //TODO:
//     // maxFrameCount
// }



void KOF_CharacterStateIdle::EnterState(int stateParam)
{
    currentFrameIndex = 0;
}

void KOF_CharacterStateIdle::ExitState(int stateParam)
{
    // KOF_CharacterFiniteStateMachineState::ExitState();
}

void KOF_CharacterStateIdle::Update()
{
    currentFrameIndex = currentFrameIndex + 1 > maxFrameCount ? 0 : currentFrameIndex + 1;
}

void KOF_CharacterStateMove::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, maxFrameCount);
}

void KOF_CharacterStateIdle::Render(HDC hdc)
{
    stateImage->Render(hdc, character->GetPos().x, character->GetPos().y, currentFrameIndex);
}

//---

// void KOF_CharacterStateMove::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
// {
//     this->character = character;
// }

void KOF_CharacterStateMove::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    isForward = stateParam == 0;
}

void KOF_CharacterStateMove::ExitState(int stateParam)
{
    // character->ResetFrame();
}

void KOF_CharacterStateMove::Update()
{
    //TODO:
    character->Move(isForward ? 1 : -1);
    // character->LoopFrame();
    currentFrameIndex = currentFrameIndex + 1 > maxFrameCount ? 0 : currentFrameIndex + 1;
}

void KOF_CharacterStateMove::Render(HDC hdc)
{
    // image[currentActionState].Render(hdc,pos.x,pos.y,currentFrameIndex,isFlip);
    stateImage[isForward ? 0 : 1].Render(hdc, character->GetPos().x, character->GetPos().y, currentFrameIndex);
}

//---

// void KOF_CharacterStateAttack::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
// {
//     this->character = character;
//     frameIndex = 0;
//     frameIndexMax = INT_MAX;
// }

void KOF_CharacterStateAttack::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, maxFrameCount);
}

void KOF_CharacterStateAttack::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    attackType = static_cast<EAttackType>(stateParam);
    switch (attackType)
    {
    case EAttackType::WEAK_PUNCH:
        character->WeakPunch();
        break;
    case EAttackType::WEAK_KICK:
        character->WeakKick();
        break;
    case EAttackType::STRONG_PUNCH:
        character->StrongPunch();
        break;
    case EAttackType::STRONG_KICK:
        character->StrongKick();
        break;
    default:
        break;
    }
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

// ---

// void KOF_CharacterStateGuard::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
// {
//     KOF_CharacterFiniteStateMachineState::Init(character);
// }

void KOF_CharacterStateGuard::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, maxFrameCount);    
}

void KOF_CharacterStateGuard::EnterState(int stateParam)
{
    currentFrameIndex = 0;
    guardHeightType = static_cast<EAttackHeightType>(stateParam);
    switch (guardHeightType)
    {
    case EAttackHeightType::NONE:
        break;
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

// ---

void KOF_CharacterStateHitStun::Init(KOF_Character* character, Image* stateImage, int maxFrameCount)
{
    KOF_CharacterFiniteStateMachineState::Init(character, stateImage, maxFrameCount);
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
