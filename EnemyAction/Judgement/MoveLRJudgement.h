#pragma once
#include "../Judgement/JudgementBase.h"

class Enemy;

// ���ړ��̔���׽
struct MoveLRJudgement :
    public JudgementBase
{
public:

    static MoveLRJudgement& getInstance(void)
    {
        static MoveLRJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

