#pragma once
#include "JudgementBase.h"

class Enemy;

// 奥行移動の判定ｸﾗｽ
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

