#pragma once
#include "JudgementBase.h"


class Enemy;

// �ړ��̔���׽
// ����̎q����MoveLR��MoveZ�ƂȂ�
struct MoveJudgement :
    public JudgementBase
{
    static MoveJudgement& getInstance(void)
    {
        static MoveJudgement sInstance_;
        return sInstance_;
    }

    bool Judgement(Enemy* enemy);
};

