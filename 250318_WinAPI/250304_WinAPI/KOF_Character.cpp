#include "KOF_Character.h"

#include "CommonFunction.h"
#include "Image.h"

void KOF_Character::WeakPunch()
{
    currentCombatInfo.damage = weakPunchDamage;
    currentCombatInfo.hitRect = RECT{ 150, 100, 235, 130};
    UpdateRect(currentCombatInfo.hitRect, pos);
    // hitRect = ;
    
    // currentCombatInfo = COMBATINFO{ hitRect, weakPunchDamage};
    isWeakPunching = true;
    
}

void KOF_Character::StrongPunch()
{
}

void KOF_Character::WeakKick()
{
}

void KOF_Character::StrongKick()
{
}

bool KOF_Character::Guard(bool)
{
    return false;
}

void KOF_Character::Init(bool isMoveable)
{
    pos = { 0.0f, 0.0f };
    moveSpeed = 5.0f;
    moveimage = new Image();
    if (FAILED(moveimage->Init(TEXT("Image/iori_walk.bmp"), 612, 104, 9, 1, 
        true, RGB(255,0,255))))
    {
        MessageBox(g_hWnd, TEXT("Image/iori_walk.bmp ���� �ε忡 ����"), TEXT("���"), MB_OK);
    }

    this->isMoveable = isMoveable;
    
    elapsedFrame = 0;
    currAnimaionFrame = 0;
}

void KOF_Character::Init(const CharacterInfo info, bool isMoveable)
{
    pos = { 0.0f, 0.0f };
    moveSpeed = 5.0f;
    
    moveimage = new Image();
    if (FAILED(moveimage->Init(
        info.spriteSheet[0].filename,
        info.spriteSheet[0].width, info.spriteSheet[0].height,
        info.spriteSheet[0].maxFrameX, info.spriteSheet[0].maxFrameY, 
        info.spriteSheet[0].isTransparent, info.spriteSheet[0].transColor)))
    {
        MessageBox(g_hWnd, info.spriteSheet[0].filename, TEXT("Warning"), MB_OK);
    }

    punchImage = new Image();
    if (FAILED(punchImage->Init(
        info.spriteSheet[1].filename,
        info.spriteSheet[1].width, info.spriteSheet[1].height,
        info.spriteSheet[1].maxFrameX, info.spriteSheet[1].maxFrameY, 
        info.spriteSheet[1].isTransparent, info.spriteSheet[1].transColor)))
    {
        MessageBox(g_hWnd, info.spriteSheet[1].filename, TEXT("Warning"), MB_OK);
    }

    health = info.health;
    weakPunchDamage = info.weakPunchDamage;
    weakKickDamage = info.weakKickDamage;
    strongPunchDamage = info.strongPunchDamage;
    strongKickDamage = info.strongKickDamage;
    characterName = info.characterName;

    hitRect = RECT{ 0, 0, 210, 180};
    // hitRect = RECT{ 0, 0, info.spriteSheet[0].width/info.spriteSheet[0].maxFrameX, info.spriteSheet[0].height/info.spriteSheet[0].maxFrameY};
    attackRect = RECT{ 0, 0, 0,0};

    this->isMoveable = isMoveable;
    
    elapsedFrame = 0;
    currAnimaionFrame = 0;
    isWeakPunching = false;
}

void KOF_Character::Release()
{
    if (moveimage)
    {
        moveimage->Release();
        delete moveimage;
        moveimage = nullptr;
    }
    
    if (punchImage)
    {
        punchImage->Release();
        delete punchImage;
        punchImage = nullptr;
    }
}

void KOF_Character::Update()
{
    elapsedFrame++;
    if (elapsedFrame % 4 == 0)
    {
        if (isWeakPunching)
        {
            currAnimaionFrame++;
            if (currAnimaionFrame > 4 )
            {
                currAnimaionFrame = 0;
                isWeakPunching = false;
                UpdateRect(currentCombatInfo.hitRect, {0,0});
                currentCombatInfo.damage = 1;
            }
            return;
        }
        //if (elapsedFrame >= 5)
        if (isMoveable)
        {
            if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
            {
                currAnimaionFrame++;
                Move(-1);

                if (currAnimaionFrame > 8)
                {
                    currAnimaionFrame = 0;
                }
                elapsedFrame = 0;
            }
            else if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
            {
                currAnimaionFrame++;
                Move(1);

                if (currAnimaionFrame > 8)
                {
                    currAnimaionFrame = 0;
                }
                elapsedFrame = 0;
            }
        }
        
        if (KeyManager::GetInstance()->IsOnceKeyDown(0x44))
        {
            WeakPunch();
            int a =0 ;
        }
        elapsedFrame = 0;
    }
    
}

void KOF_Character::Render(HDC hdc)
{
    if (isWeakPunching && punchImage)
    {
        // RenderRect(hdc, pos.x + 150, pos.y + 100, 85, 30);
        // RenderRect(hdc, pos.x + 65 * ( pos.x > 400 ? -0 : 0), pos.y, 150, 180);
        punchImage->Render(hdc, pos.x + 65 * ( pos.x > 400 ? -0 : 0), pos.y, currAnimaionFrame, !isMoveable);
        
    }
    else if (moveimage)
        // RenderRect(hdc, pos.x + 65 * ( pos.x > 400 ? -0 : 0), pos.y, 150, 180);
        moveimage->Render(hdc, pos.x, pos.y, currAnimaionFrame, !isMoveable);
}

int KOF_Character::GetHealth() { return health; }

RECT KOF_Character::GetHitRect() { return hitRect; }

RECT KOF_Character::GetAttackRect() { return attackRect; }

// Attack KOF_Character::GetCurrentAttack()
// {
//     return Attack{0, &attackRect };
// }

void KOF_Character::GetDamage(int damage)
{
    health -= damage;
}

//TODO:
void KOF_Character::Move()
{
    pos.x += moveSpeed;
}

void KOF_Character::Move(int dirX)
{
    pos.x += moveSpeed * dirX;
    UpdateRect(hitRect, pos);
}

void KOF_Character::ResetAttack()
{
    currentCombatInfo.damage = 0; UpdateRect(currentCombatInfo.hitRect, {0,0});
}