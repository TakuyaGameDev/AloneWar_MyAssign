#pragma once
#include "../Action/ActionBase.h"

// �ʏ�U���̎��s�׽
struct NormalAttackAction :
    public ActionBase
{
public:
    static NormalAttackAction& getInstance(void)
    {
        static NormalAttackAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

