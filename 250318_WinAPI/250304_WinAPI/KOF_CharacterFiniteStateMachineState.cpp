#include "KOF_CharacterFiniteStateMachineState.h"
#include "KOF_Character.h"

void KOF_CharacterStateMove::Init(KOF_Character* character)
{
    this->character = character;
}

void KOF_CharacterStateMove::EnterState()
{
    //frame 0
}

void KOF_CharacterStateMove::ExitState()
{
    character->ResetFrame();
}

void KOF_CharacterStateMove::Update()
{
    character->Move(character->GetIsFlip() ? -1 : 1);
    character->LoopFrame();
}

void KOF_CharacterStateMove::Render()
{
    image[currentActionState].Render(hdc,pos.x,pos.y,currentFrameIndex,isFlip);
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
