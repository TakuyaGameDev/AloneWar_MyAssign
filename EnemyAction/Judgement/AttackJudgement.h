#pragma once
#include "JudgementBase.h"

class Enemy;

// �U���s���̔���׽
struct AttackJudgement :
    public JudgementBase
{
public:

    static AttackJudgement& getInstance(void)
    {
        static AttackJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

