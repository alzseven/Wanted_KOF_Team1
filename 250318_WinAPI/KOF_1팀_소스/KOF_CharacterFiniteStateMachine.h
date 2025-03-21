#pragma once
#include "config.h"

class KOF_CharacterFiniteStateMachineState;

class KOF_CharacterFiniteStateMachine
{
private:
    KOF_CharacterFiniteStateMachineState** states;
    int currentState;
public:
    void Init(KOF_CharacterFiniteStateMachineState** states);
    void Update();
    void Render(HDC hdc, bool isFlip = false);
    void SetState(int state, int exitStateParam = 0, int enterStateParam = 0);
    void Release();
};
