#pragma once
#include "../Action/ActionBase.h"


class Enemy;
// ���ړ��̱���ݎ��s�׽
struct MoveLRAction :
    public ActionBase
{
public:
    static MoveLRAction& getInstance(void)
    {
        static MoveLRAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

