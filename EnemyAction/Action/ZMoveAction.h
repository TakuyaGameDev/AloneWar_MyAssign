#pragma once
#include "../Action/ActionBase.h"

class Enemy;


// ���s���s�̱���ݎ��s�׽
struct ZMoveAction :
    public ActionBase
{
public:

    static ZMoveAction& getInstance(void)
    {
        static ZMoveAction sInstance_;
        return sInstance_;
    }

    void Run(Enemy* enemy);
};

