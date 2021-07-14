#pragma once
#include "JudgementBase.h"

class Enemy;

// skillAttack�̔���׽
struct SkillAttackJudgement :
    public JudgementBase
{
public:

    static SkillAttackJudgement& getInstance(void)
    {
        static SkillAttackJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

