#pragma once
#include "config.h"

class KOF_Character;

class KOF_CharacterFiniteStateMachineState
{
protected:
    KOF_Character* character;

public:
    virtual void Init(KOF_Character* character);
    virtual void EnterState();
    virtual void ExitState();
    virtual void Update();
    virtual void Render();
};

class KOF_CharacterStateIdle : public KOF_CharacterFiniteStateMachineState
{
public:
    void Init(KOF_Character* character) override;
    void EnterState() override;
    void ExitState() override;
    void Update() override;
    void Render() override;
};

class KOF_CharacterStateMove : public KOF_CharacterFiniteStateMachineState
{
public:
    void Init(KOF_Character* character) override;
    void EnterState() override;
    void ExitState() override;
    void Update() override;
    void Render() override;
};

class KOF_CharacterStateAttack : public KOF_CharacterFiniteStateMachineState
{
private:
    int frameIndex;
    int frameIndexMax;
public:
    void Init(KOF_Character* character) override;
    void EnterState() override;
    void ExitState() override;
    void Update() override;
    void Render() override;
    void SetFrameIndexMax(int frameIndexMax);
};

class KOF_CharacterStateGuard : public KOF_CharacterFiniteStateMachineState
{
public:
    void Init(KOF_Character* character) override;
    void EnterState() override;
    void ExitState() override;
    void Update() override;
    void Render() override;
};