#include "KOF_CharacterFiniteStateMachine.h"
#include "KOF_CharacterFiniteStateMachineState.h"
#include "KOF_CharacterState.h"

void KOF_CharacterFiniteStateMachine::Init(KOF_CharacterFiniteStateMachineState* states)
{
    this->states = states;
    currentState = static_cast<int>(State::Idle);
}

void KOF_CharacterFiniteStateMachine::Update()
{
    states[currentState].Update();
}

void KOF_CharacterFiniteStateMachine::Render(HDC hdc)
{
    states[currentState].Render(hdc);
}

void KOF_CharacterFiniteStateMachine::SetState(int state)
{
    states[currentState].ExitState();
    currentState = state;
    states[currentState].EnterState();
}

int KOF_CharacterFiniteStateMachine::GetState()
{
    return currentState;
}
