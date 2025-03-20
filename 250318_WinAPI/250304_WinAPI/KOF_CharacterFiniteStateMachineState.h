#pragma once
#include "config.h"

enum class EAttackType;
class Image;
class KOF_Character;

class KOF_CharacterFiniteStateMachineState
{
protected:
    KOF_Character* character;
    Image* stateImage;
    int currentFrameIndex;
    int maxFrameCount;
public:
    // virtual ~KOF_CharacterFiniteStateMachineState();

    virtual void Init(KOF_Character* character, Image* stateImage, int maxFrameCount);
    virtual void EnterState(int stateParam = 0) = 0;
    virtual void ExitState(int stateParam = 0) = 0;
    virtual void Update() = 0;
    void Release();
    virtual void Render(HDC hdc) = 0;
};

class KOF_CharacterStateIdle : public KOF_CharacterFiniteStateMachineState
{
public:
    void Init(KOF_Character* character, Image* stateImage, int maxFrameCount) override;
    void EnterState(int stateParam = 0) override;
    void ExitState(int stateParam = 0) override;
    void Update() override;
    void Render(HDC hdc) override;
    // ~KOF_CharacterStateIdle() override;
};

class KOF_CharacterStateMove : public KOF_CharacterFiniteStateMachineState
{
    bool isForward;
public:
    void Init(KOF_Character* character, Image* stateImage, int maxFrameCount) override;
    void EnterState(int stateParam = 0) override;
    void ExitState(int stateParam = 0) override;
    void Update() override;
    void Render(HDC hdc) override;
};

class KOF_CharacterStateAttack : public KOF_CharacterFiniteStateMachineState
{
private:
    EAttackType attackType;
public:
    void Init(KOF_Character* character, Image* stateImage, int maxFrameCount) override;
    void EnterState(int stateParam = 0) override;
    void ExitState(int stateParam = 0) override;
    void Update() override;
    void Render(HDC hdc) override;
    void SetFrameIndexMax(int frameIndexMax);
};

class KOF_CharacterStateGuard : public KOF_CharacterFiniteStateMachineState
{
private:
    EAttackHeightType guardHeightType;    
public:
    void Init(KOF_Character* character, Image* stateImage, int maxFrameCount) override;
    void EnterState(int stateParam = 0) override;
    void ExitState(int stateParam = 0) override;
    void Update() override;
    void Render(HDC hdc) override;
};