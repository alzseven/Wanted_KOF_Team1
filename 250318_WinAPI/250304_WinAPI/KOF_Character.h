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
    //TODO : 
    FPOINT pos;
    float moveSpeed;
    string characterName;
    RECT hitRect;
    RECT attackRect;

    Image* moveimage;
    Image* punchImage;
    int elapsedFrame;
    int currAnimaionFrame;

    bool isWeakPunching;
    bool isMoveable;
    COMBATINFO currentCombatInfo;

public:
    void WeakPunch();
    void StrongPunch();
    void WeakKick();
    void StrongKick();
    bool Guard(bool);

    void Init(bool isMoveable = true);
    void Init(const CharacterInfo info, bool isMoveable = true);
    void Release();
    void Update();
    void Render(HDC hdc);
    //---
    int GetHealth();
    RECT GetHitRect();
    RECT GetAttackRect();

    //TODO:
    inline COMBATINFO GetCurrentAttack(){ return this->currentCombatInfo;}
    void ResetAttack();
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


