#include "KOF_CharacterFiniteStateMachine.h"
#include "KOF_CharacterFiniteStateMachineState.h"

void KOF_CharacterFiniteStateMachine::Init(KOF_CharacterFiniteStateMachineState* states)
{
    this->states = states;
    currentState = 0;
}

void KOF_CharacterFiniteStateMachine::Update()
{
    states[currentState].Update();
}

void KOF_CharacterFiniteStateMachine::SetState(int state)
{
    states[currentState].ExitState();
    currentState = state;
    states[currentState].EnterState();
}
