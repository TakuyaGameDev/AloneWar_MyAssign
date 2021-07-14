#pragma once
#include <array>
#include "ObjectPool.h"
#include "../ENEMYTYPE.h"
#include "../EnemyAction/BehaviorTree.h"

class Actor;
class Enemy;
class Player;

// �G�����ߐ��̎v�lٰ�ݔz��
using Behavior = std::array<BehaviorTree, static_cast<int>(ENEMYTYPE::Max)>;
// �G�̔���ۊǂ��Ă����ޯ̧(ObjectPooling�@)
class EnemyPool :
    public ObjectPool
{
public:
    EnemyPool();
    ~EnemyPool();
    // pool�̐���
    void Create(int size,std::shared_ptr<Player>& player);
    // pool�̒����玀��ł����̏E���グ
    std::shared_ptr<Enemy>& Pickup(int spawnCnt);
    // pool�̔j��(Game�̏I�����Ɏg�p)
    void Destroy(void);
    // pool�̒��g�����ް�̍X�V(�����Ă����̂�)
    void Update(void);
    // pool�̒��g�����ް�̕`��(�����Ă����̂�)
    void Draw(void);
    // ColliderBox�̕`��(debug�\��)
    void DrawCollider(void);

    // ���߂ɍ��킹����Ͳ�ޱ�ذ�̍쐬
    void BehaviorRegistrator(ENEMYTYPE type);

private:
    // pool�ɗ��܂��Ă���G����
    std::vector<std::shared_ptr<Enemy>> poolMembers_;
    // pool����E���グ��G�ɗ^������Ͳ�ޱ�ް�
    // ���ߖ��ɈقȂ�
    Behavior behaviors_;
};

