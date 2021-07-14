#pragma once
#include "JudgementBase.h"

class Enemy;

// �U������s���̔���׽
struct AvoidanceJudgement :
    public JudgementBase
{
    static AvoidanceJudgement& getInstance(void)
    {
        static AvoidanceJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

