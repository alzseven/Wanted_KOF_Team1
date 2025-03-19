#pragma once

class KOF_CharacterFiniteStateMachineState;

class KOF_CharacterFiniteStateMachine
{
private:
    KOF_CharacterFiniteStateMachineState* states;
    int currentState;
public:
    void Init(KOF_CharacterFiniteStateMachineState* states);
    void Update();
    void SetState(int state);
};
