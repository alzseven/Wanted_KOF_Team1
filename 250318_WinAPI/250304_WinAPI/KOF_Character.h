#pragma once
#include "CommonFunction.h"
#include "GameObject.h"
#include "KOF_CharacterState.h"

enum class EFiniteStateMachineState;
class KOF_CharacterStateGuard;
class KOF_CharacterStateAttack;
class KOF_CharacterStateMove;
class KOF_CharacterStateIdle;
class KOF_CharacterFiniteStateMachineState;
class KOF_CharacterFiniteStateMachine;
class Image;

class KOF_Character : public GameObject
{
private:
    int health;
    int weakPunchDamage;
    int weakKickDamage;
    int strongPunchDamage;
    int strongKickDamage;
    FPOINT pos;
    float moveSpeed;
    string characterName;
    RECT hitRect;
    RECT attackRect;
    RECT rcCollision;

    int currAnimaionFrame;

    // bool isWeakPunching;
    bool isMoveable;
    COMBATINFO currentCombatInfo;
    UIINFO uiInfo;

    Image* image;
    int currentFrameIndex;

    // 현재 캐릭터의 상태 저장
    int currentActionState;
    float elaspedFrame;

    bool isFlip;

    KOF_CharacterFiniteStateMachine* fsm;
    KOF_CharacterFiniteStateMachineState** states;

    EFiniteStateMachineState currentMachinState;
    KOF_CharacterStateIdle *idleState;
    KOF_CharacterStateMove *moveState;
    KOF_CharacterStateAttack *attackState;
    KOF_CharacterStateGuard *guardState;

    EAttackHeightType guardHeight;
    // FPOINT* enemyPos;
    KOF_Character* enemy;
public:
    void WeakPunch();
    void StrongPunch();
    void WeakKick();
    void StrongKick();
    bool Guard(bool);

    
    // void Init(bool isMoveable = true);
    void Init(const CharacterInfo info, bool isMoveable = true, bool isFlip = false);
    void Release();
    void Update();
    void Render(HDC hdc);
    //---

    inline int GetHealth() const { return health; }
    inline RECT GetHitRect() const { return hitRect; }
    inline RECT GetAttackRect() const { return attackRect; }
    inline RECT GetRcCollision() const { return rcCollision; }
    
    void CheckAttack();

    //TODO:
    inline COMBATINFO GetCurrentAttack(){ return this->currentCombatInfo;}
    inline void ResetAttack()
    {
        currentCombatInfo.damage = 0; UpdateRect(currentCombatInfo.hitRect, {0,0});
        currentCombatInfo.attackHeightType = EAttackHeightType::NONE;
    }
    void GetDamage(int damage);
    void GetDamage(int damage, EAttackHeightType attackHeight);
    void Move();
    void Move(int dirX);
    inline void SetPos(FPOINT pos)
    {
        this->pos = pos;
        UpdateRect(hitRect, pos);
        // UpdateRect(attackRect, pos);
    }
    bool GetIsFlip() const { return this->isFlip;}
    inline FPOINT GetPos() const { return this->pos;}
    void SetStateToIdle();
    inline void SetGuardHeight(EAttackHeightType guardHeight){this->guardHeight = guardHeight;}
    inline EAttackHeightType GetGuardHeight() const { return this->guardHeight;}

    inline void SetEnemy(KOF_Character* pEnemy) {this->enemy = pEnemy;}
    // inline void SetEnemyPos(FPOINT* pEnemyPos) { this->enemyPos = pEnemyPos;}
    inline EFiniteStateMachineState GetCurrentMachinState() const { return this->currentMachinState;}
};


