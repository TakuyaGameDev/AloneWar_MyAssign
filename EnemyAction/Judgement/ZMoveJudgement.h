#pragma once
#include "JudgementBase.h"

class Enemy;

// ���s�ړ��̔���׽
struct ZMoveJudgement :
    public JudgementBase
{
public:

    static ZMoveJudgement& getInstance(void)
    {
        static ZMoveJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

