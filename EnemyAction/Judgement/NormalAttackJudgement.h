#pragma once
#include "JudgementBase.h"

class Enemy;

// ΚνUΜ»θΈΧ½
struct NormalAttackJudgement :
    public JudgementBase
{
public:

    static NormalAttackJudgement& getInstance(void)
    {
        static NormalAttackJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

