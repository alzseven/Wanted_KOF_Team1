#include "KOF_CharacterFiniteStateMachine.h"
#include "KOF_CharacterFiniteStateMachineState.h"

void KOF_CharacterFiniteStateMachine::Init(KOF_CharacterFiniteStateMachineState** states)
{
    this->states = states;
    currentState = 0;
}

void KOF_CharacterFiniteStateMachine::Update()
{
    states[currentState]->Update();
}

void KOF_CharacterFiniteStateMachine::SetState(int state, int exitStateParam, int enterStateParam)
{
    states[currentState]->ExitState(exitStateParam);
    currentState = state;
    states[currentState]->EnterState(enterStateParam);
}

void KOF_CharacterFiniteStateMachine::Release()
{
    if (states)
        delete states;
}

void KOF_CharacterFiniteStateMachine::Render(HDC hdc)
{
    states[currentState]->Render(hdc);
}

