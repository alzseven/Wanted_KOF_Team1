#pragma once
#include "CommonFunction.h"
#include "GameObject.h"
#include "KOF_CharacterState.h"

class KOF_CharacterStateHitStun;
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
    int maxHealth;
    int health;
    
    FPOINT pos;
    float moveSpeed;
    
    string characterName;
    RECT hitRect;
    RECT attackRect;
    RECT rcCollision;

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
    KOF_CharacterStateHitStun *hitStunState;
    EAttackHeightType guardHeight;
    // FPOINT* enemyPos;
    KOF_Character* enemy;

    int playerNum;
    // Key

    int MOVEFOWARD;
    int MOVEBACKWARD;
    int SIT_DOWN;
    int ATTACK_WEAK_PUNCH;
    int ATTACK_STRONG_PUNCH;
    int ATTACK_WEAK_KICK;
    int ATTACK_STRONG_KICK;

    StateFrameInfo* actionInfo;
public:
    void Attack(EAttackType attackType);
    // void WeakPunch();
    // void StrongPunch();
    // void WeakKick();
    // void StrongKick();
    // bool Guard(bool);
    
    void Init(const CharacterInfo characterInfo, int playerNum, bool isFlip = false, bool isMoveable = true);
    void Release();
    void Update();
    void Render(HDC hdc);
    //---

    inline int GetMaxHealth() const { return maxHealth; }
    inline int GetHealth() const { return health; }
    inline RECT GetHitRect() const { return hitRect; }
    inline RECT GetAttackRect() const { return attackRect; }
    inline RECT GetRcCollision() const { return rcCollision; }
    
    void CheckAttack();

    //TODO:
    inline COMBATINFO GetCurrentAttack(){ return this->currentCombatInfo;}
    void ResetAttack();
    // {
    //     currentCombatInfo.damage = 0;
    //     UpdateRect(currentCombatInfo.attackRect, {0,0});
    //     currentCombatInfo.attackHeightType = EAttackHeightType::NONE;
    // }
    // void GetDamage(int damage);
    void GetDamage(int damage, EAttackHeightType attackHeight);
    // void Move();
    // void Move(int dirX);
    void Move(EMoveType moveType);
    void SetPos(FPOINT pos);
    void ChangeState(EFiniteStateMachineState newState, const StateFrameInfo& newActionInfo, int exitStateParam = 0, int enterStateParam = 0);
    bool GetIsFlip() const { return this->isFlip;}
    inline FPOINT GetPos() const { return this->pos;}
    void SetStateToIdle();
    inline void SetGuardHeight(EAttackHeightType guardHeight){this->guardHeight = guardHeight;}
    inline EAttackHeightType GetGuardHeight() const { return this->guardHeight;}

    inline void SetEnemy(KOF_Character* pEnemy) {this->enemy = pEnemy;}
    // inline void SetEnemyPos(FPOINT* pEnemyPos) { this->enemyPos = pEnemyPos;}
    inline EFiniteStateMachineState GetCurrentMachinState() const { return this->currentMachinState;}
};


