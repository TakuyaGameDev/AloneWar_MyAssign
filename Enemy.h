#pragma once
#include "Actor.h"
#include "../ENEMYTYPE.h"
#include "../EnemyAction/BehaviorTree.h"

// Z����������׽ϲŽ�ǂ��炩�Ɉړ����邩������
enum class ZPosFromPlayer
{
    // ��ڲ԰��Z������ϲŽ�ɂ���ꍇ
    Minus,
    // ��ڲ԰��Z��������׽�ɂ���ꍇ
    Plus,
    // ��ڲ԰��Z���Ƃ̍������ȉ��̏ꍇ
    Non,
    Max
};

// ����������
enum class MoveType
{
    // ���E���ɓ���
    MoveLR,
    // ���s�ɓ���
    MoveZ,
    // �����Ȃ�
    Non,
    Max
};

// �����̎��E
struct VisionRange
{
    // run��Ұ��݂��s�����E
    float runRange_;
    // attack��Ұ��݂��s�����E
    float attackRange_;

    VisionRange() :runRange_(0.0f), attackRange_(0.0f) {};
    VisionRange(float runR, float atR) :runRange_(runR), attackRange_(atR) {};
};

// �e��Ұ��݂̎��s�֐��߲��
typedef void(Enemy::* AnimExcecuter)();

class BehaviorData;
class ActionNode;
class Player;

class Enemy :
    public Actor
{
public:
    Enemy(int hp, std::shared_ptr<Player>& player);
    ~Enemy();
    // �X�V
    void Action(void);
    // ���E�̓���
    void Move(void);
    // Z�������킹�鱸���
    void ZMove(void);
    // �U��(Actor����̌p��)
    void Attack(void);
    // Attack�֐��Ɋ܂߂邽�߂̽�ٍU���֐�(�����̓G�����ߖ��ɕ���)
    void SkillAttack(ENEMYTYPE type);
    // ����s��
    void Avoidance(void);
    // ������
    virtual bool Initialize(void) { return false; };
    // pool�̒����玀��ł�����pickUp����̂�pickUp����������߂�^���Ă������
    // �߼޼�݂�Ă��Ă��֐�
    void SetEnemy(ENEMYTYPE type,Vector3F pos);
    // ��Ͳ�ޱ�ذ�̾��
    void SetBehavior(BehaviorTree* behaviorTree);
    // �G���߂̾�Ċ֐�
    void Set(ENEMYTYPE type);
    // ���E�̎擾
    const VisionRange& GetVisionRange(void)
    {
        return visionRange_;
    }
    // �����߼޼�݂Ƃ̋������v�Z���Ď擾
    const Vector3F& GetDistance(void);
    // ���ޯ�ޕ\��
    void DebugDraw(void);
    // Z��������ϲŽ�����ɓ������̂���׽�����ɓ������̂��̾�Ċ֐�
    void SetZPosStatus(ZPosFromPlayer zStatus);
    // ��Ұ��ݎ��s�֐��Ɏ��s�֐��̾��
    void SetAnimExcecuter(void(Enemy::* func)());

    // ��Ͳ�ޱ�ذ�̎擾�֐�
    BehaviorTree* GetBehaviorTree(void)
    {
        return behaviorTree_;
    }
   
    // ���������߂̎擾
    const MoveType& GetMoveType(void)
    {
        return moveType_;
    }
    // ���������߂̾��
    void SetMoveType(MoveType moveType);

    // ���������Ă�����ڲ԰�̎擾
    const std::shared_ptr<Player>& GetPlayer(void)
    {
        return player_;
    }
    // �s�����s�֐��߲���擾�֐�
    const AnimExcecuter& GetAnimExcecuter(void)
    {
        return animExcecuter_;
    }
    // ��ق������Ă����true��Ԃ�
    const bool& HasSkill(void)
    {
        return hasSkill_;
    }

private:

protected:
    // �s���̎��s�֐��߲��
    AnimExcecuter animExcecuter_;
    // ���������ߕϐ�
    ENEMYTYPE myType_;
    // ���M����Ͳ�ޱ�ذ(�v�l)
    BehaviorTree* behaviorTree_;
    // ��Ͳ�ޱ�ް�(sequence�����ް�)
    BehaviorData* behaviorData_;
    // ���sɰ��
    ActionNode* runningNode_;
    // ���E
    VisionRange visionRange_;
    // ��ڲ԰�̎Q��
    std::shared_ptr<Player>& player_;
    // ��ڲ԰�ɑ΂��Ă̎�����Z���̏��
    ZPosFromPlayer zPosStatus_;
    // ���������ߕϐ�
    MoveType moveType_;
    // �����蔻����󂯕t���Ȃ��׸�
    bool noAcceptHitFlag_;
    // ��ق������Ă��邩���׸�
    bool hasSkill_;
};

