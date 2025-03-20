#include "KOF_CharacterFiniteStateMachineState.h"
#include "KOF_Character.h"

void KOF_CharacterStateMove::Init(KOF_Character* character)
{
    this->character = character;
    frameIndex = 0;
    frameIndexMax = 6;
}

void KOF_CharacterStateMove::EnterState()
{
    frameIndex = 0;
}

void KOF_CharacterStateMove::ExitState()
{
    character->ResetFrame();
}

void KOF_CharacterStateMove::Update()
{
    character->Move(character->GetIsFlip() ? -1 : 1);
    character->LoopFrame(frameIndexMax);
}

void KOF_CharacterStateMove::Render(HDC hdc)
{
    // TODO
}

//---

void KOF_CharacterStateAttack::Init(KOF_Character* character)
{
    this->character = character;
    frameIndex = 0;
    frameIndexMax = INT_MAX;
}

void KOF_CharacterStateAttack::EnterState()
{
    frameIndex = 0;     
    frameIndexMax = INT_MAX;
}

void KOF_CharacterStateAttack::ExitState()
{

}

void KOF_CharacterStateAttack::Update()
{
    frameIndex++;
    if (frameIndex > frameIndexMax) character->ReturnToIdle();
}

void KOF_CharacterStateAttack::Render(HDC hdc)
{
}

void KOF_CharacterStateAttack::SetFrameIndexMax(int frameIndexMax)
{
}

void KOF_CharacterStateIdle::Init(KOF_Character* character)
{
}

void KOF_CharacterStateIdle::EnterState()
{
}

void KOF_CharacterStateIdle::ExitState()
{
}

void KOF_CharacterStateIdle::Update()
{
}

void KOF_CharacterStateIdle::Render(HDC hdc)
{

}

void KOF_CharacterStateGuard::Init(KOF_Character* character)
{

}

void KOF_CharacterStateGuard::EnterState()
{

}

void KOF_CharacterStateGuard::ExitState()
{

}

void KOF_CharacterStateGuard::Update()
{

}

void KOF_CharacterStateGuard::Render(HDC hdc)
{

}
