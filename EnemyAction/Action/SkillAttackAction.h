#pragma once
#include "ActionBase.h"

class Enemy;


// skillAttack�̎��s�׽
struct SkillAttackAction :
    public ActionBase
{
public:

    static SkillAttackAction& getInstance(void)
    {
        static SkillAttackAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

