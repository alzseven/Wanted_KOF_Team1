#pragma once
#include "CommonFunction.h"
#include "GameObject.h"

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
    int playerNum;
    RECT hitRect;
    RECT attackRect;


    int currAnimaionFrame;

    bool isWeakPunching;
    bool isMoveable;
    COMBATINFO currentCombatInfo;
    UIINFO uiInfo;

    // Key

    int MOVEFOWARD;
    int MOVEBACKWARD;

    int ATTACK_WEAK_PUNCH;
    int ATTACK_STRONG_PUNCH;
    int ATTACK_WEAK_KICK;
    int ATTACK_STRONG_KICK;

    Image* image;
    int currentFrameIndex;

    // 현재 캐릭터의 상태 저장
    int currentActionState;
    float elaspedFrame;

    bool isFlip;



public:
    void WeakPunch();
    void StrongPunch();
    void WeakKick();
    void StrongKick();
    bool Guard(bool);

    
<<<<<<< Updated upstream
    void Init(bool isMoveable = true);
    void Init(const CharacterInfo info, bool isMoveable = true, bool isFlip = false);
=======
    // void Init(bool isMoveable = true);
    void Init(const CharacterInfo info, bool isMoveable = true, bool isFlip = false, int playerNum);
>>>>>>> Stashed changes
    void Release();
    void Update();
    void Render(HDC hdc);
    void LoopFrame(int frameIndexMax);
    void ResetFrame();
    void ReturnToIdle();

    //---
    int GetHealth();
    RECT GetHitRect();
    RECT GetAttackRect();



    //TODO:
    inline COMBATINFO GetCurrentAttack(){ return this->currentCombatInfo;}
    inline void ResetAttack(){ currentCombatInfo.damage = 0; currentCombatInfo.hitRect.left = 0; currentCombatInfo.hitRect.top = 0;}
    void GetDamage(int damage);
    void Move();
    void Move(int dirX);
    inline void SetPos(FPOINT pos)
    {
        this->pos = pos;
        UpdateRect(hitRect, pos);
        UpdateRect(attackRect, pos);
    }    
};


