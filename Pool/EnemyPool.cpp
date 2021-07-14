#include "../Pool/EnemyPool.h"
#include "../Actor/Enemy.h"
#include "../Actor/Player.h"

// ��Ͳ�ޱ�ް����\�����邽�߂̲ݸٰ��-------------------
#include "../EnemyAction/BehaviorTree.h"
#include "../EnemyAction/Judgement/AttackJudgement.h"
#include "../EnemyAction/Judgement/MoveJudgement.h"
#include "../EnemyAction/Action/MoveLRAction.h"
#include "../EnemyAction/Judgement/MoveLRJudgement.h"
#include "../EnemyAction/Action/NormalAttackAction.h"
#include "../EnemyAction/Judgement/NormalAttackJudgement.h"
#include "../EnemyAction/Action/SkillAttackAction.h"
#include "../EnemyAction/Judgement/SkillAttackJudgement.h"
#include "../EnemyAction/Action/ZMoveAction.h"
#include "../EnemyAction/Judgement/ZMoveJudgement.h"
#include "../EnemyAction/Action/AvoidanceAction.h"
#include "../EnemyAction/Judgement/AvoidanceJudgement.h"
//------------------------------------------------------

EnemyPool::EnemyPool()
{

}

EnemyPool::~EnemyPool()
{
}

void EnemyPool::Create(int size, std::shared_ptr<Player>& player)
{
	// size�ɉ�����pool�̑傫�������܂�
	for (int s = 0; s < size; s++)
	{
		// �܂��Ƃɂ����G�̔���p��
		poolMembers_.push_back(std::make_shared<Enemy>(10,player));
	}
	// pool�̻���
	poolSize_ = size;
}

std::shared_ptr<Enemy>& EnemyPool::Pickup(int spawnCnt)
{
	for (int s = 0; s < spawnCnt; s++)
	{
		// pool�̻��ނŉ�
		for (int i = 0; i < poolSize_; i++) 
		{
			// ����ł����������pool����E���グ��
			if (!poolMembers_[i]->GetAlive()) 
			{
				// �����Ԃ点��
				poolMembers_[i]->SetAlive(true);
				// HP�̏�����
				poolMembers_[i]->SetHP(10);
				// ��Ͳ�ޱ�ް��̱���
				poolMembers_[i]->SetBehavior(&behaviors_[static_cast<int>(ENEMYTYPE::Cultist)]);
				// �G�̾��
				poolMembers_[i]->SetEnemy(ENEMYTYPE::Cultist, Vector3F(300.0f, 100.0f, 100.0f));
				// ���g�p�Ȃ̂ōė��p�\
				return poolMembers_[i];
			}
		}
	}
}

void EnemyPool::Destroy(void)
{
	for (auto itr = poolMembers_.begin(); itr != poolMembers_.end(); itr++)
	{
		poolMembers_.erase(itr);
	}
}

void EnemyPool::Update(void)
{
	for (int i = 0; i < poolSize_; i++) 
	{
		// �����Ă����
		if (poolMembers_[i]->GetAlive())
		{
			// �X�V
			poolMembers_[i]->Update();
		}
	}
}

void EnemyPool::Draw(void)
{
	for (auto member : poolMembers_)
	{
		// �����Ă����
		if (member->GetAlive())
		{
			// �`��
			member->Draw();
		}
	}
}

void EnemyPool::DrawCollider(void)
{
	for (auto member : poolMembers_)
	{
		// �����Ă����
		if (member->GetAlive())
		{
			// �ײ�ް�ޯ���̕`��
			member->DebugColliderDraw();
		}
	}
}

void EnemyPool::BehaviorRegistrator(ENEMYTYPE type)
{
	// �܂�ٰĂ̐���
	behaviors_[static_cast<int>(type)].AddNode("", "root", 0,BehaviorTree::SelectRule::Priority, nullptr, nullptr);
	switch (type)
	{
	case ENEMYTYPE::CultistAssassin:
		// �ړ��̔���׽�Ǝ��s�׽�̊i�[(root -> moveɰ�ނɌq����)
		behaviors_[static_cast<int>(type)].AddNode("root", "move", 3,
													BehaviorTree::SelectRule::Random,
													&MoveJudgement::getInstance(), 
													nullptr);
		// �U���̔���׽�Ǝ��s�׽�̊i�[(root -> attackɰ�ނɌq����)
		behaviors_[static_cast<int>(type)].AddNode("root", "attack", 2,
													BehaviorTree::SelectRule::Sequence,
													&AttackJudgement::getInstance(), 
													nullptr);
		// ����s���̔���׽�Ǝ��s�׽�̊i�[(root -> avoidance�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("root", "avoidance", 1,
													BehaviorTree::SelectRule::Non, 
													&AvoidanceJudgement::getInstance(),
													&AvoidanceAction::getInstance());
		// ���ړ��s���̔���׽�Ǝ��s�׽�̊i�[(root -> move -> moveLR�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveLR", 1,
													BehaviorTree::SelectRule::Non,
													&MoveLRJudgement::getInstance(), 
													&MoveLRAction::getInstance());
		// ���ړ��s���̔���׽�Ǝ��s�׽�̊i�[(root -> move -> moveZ�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveZ", 2,
													BehaviorTree::SelectRule::Non,
													&ZMoveJudgement::getInstance(), 
													&ZMoveAction::getInstance());
		// ���ʂ̍U���s���̔���׽�Ǝ��s�׽�̊i�[(root -> attack -> normalAttack�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("attack", "normalAttack", 1,
													BehaviorTree::SelectRule::Non,
													&NormalAttackJudgement::getInstance(), 
													&NormalAttackAction::getInstance());
		// skillAttack�s���̔���׽�Ǝ��s�׽�̊i�[(root -> attack -> skilAttack�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("attack", "skillAttack", 2,
													BehaviorTree::SelectRule::Non, 
													&SkillAttackJudgement::getInstance(), 
													&SkillAttackAction::getInstance());
		
		break;
	case ENEMYTYPE::Cultist:
		// �ړ��̔���׽�Ǝ��s�׽�̊i�[(root -> moveɰ�ނɌq����)
		behaviors_[static_cast<int>(type)].AddNode("root", "move", 3,
													BehaviorTree::SelectRule::Random,
											        &MoveJudgement::getInstance(),
													nullptr);
		// �U���̔���׽�Ǝ��s�׽�̊i�[(root -> attackɰ�ނɌq����)
		behaviors_[static_cast<int>(type)].AddNode("root", "attack", 2,
													BehaviorTree::SelectRule::Sequence,
												    &AttackJudgement::getInstance(),
													nullptr);
		// ����s���̔���׽�Ǝ��s�׽�̊i�[(root -> avoidance�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("root", "avoidance", 1, 
													BehaviorTree::SelectRule::Non,
												    &AvoidanceJudgement::getInstance(), 
												    &AvoidanceAction::getInstance());
		// ���ړ��s���̔���׽�Ǝ��s�׽�̊i�[(root -> move -> moveLR�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveLR", 1, 
													BehaviorTree::SelectRule::Non,
												    &MoveLRJudgement::getInstance(),
												    &MoveLRAction::getInstance());
		// ���ړ��s���̔���׽�Ǝ��s�׽�̊i�[(root -> move -> moveZ�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("move", "moveZ", 2,
													BehaviorTree::SelectRule::Non,
												    &ZMoveJudgement::getInstance(),
													&ZMoveAction::getInstance());
		// ���ʂ̍U���s���̔���׽�Ǝ��s�׽�̊i�[(root -> attack -> normalAttack�ƌq����)
		behaviors_[static_cast<int>(type)].AddNode("attack", "normalAttack", 1, 
													BehaviorTree::SelectRule::Non,
												    &NormalAttackJudgement::getInstance(),
												    &NormalAttackAction::getInstance());
		break;
	case ENEMYTYPE::TwistedCultist:
		break;
	case ENEMYTYPE::Max:
		break;
	default:
		break;
	}
}
