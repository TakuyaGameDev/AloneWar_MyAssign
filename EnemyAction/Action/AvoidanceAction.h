#pragma once
#include "ActionBase.h"

class Enemy;

// �U���������s���׽
struct AvoidanceAction :
    public ActionBase
{
    static AvoidanceAction& getInstance(void)
    {
        static AvoidanceAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

