#include "../Actor/Enemy.h"
#include "../Actor/Player.h"

#include "../EnemyAction/Action/MoveLRAction.h"
#include "../EnemyAction/Judgement/MoveLRJudgement.h"
#include "../EnemyAction/Action/ZMoveAction.h"
#include "../EnemyAction/Judgement/ZMoveJudgement.h"
#include "../EnemyAction/Action/NormalAttackAction.h"
#include "../EnemyAction/Judgement/NormalAttackJudgement.h"
#include "../EnemyAction/Action/SkillAttackAction.h"
#include "../EnemyAction/Judgement/SkillAttackJudgement.h"

#include "../EnemyAction/BehaviorData.h"

#include "../CollisionCheck.h"
#include "../DataCache.h"

Enemy::Enemy(int hp, std::shared_ptr<Player>& player):
	Actor(hp),player_(player)
{
	// �����Ă����׸ނ̏�����
	isAlive_ = false;
	// �����蔻���׸ނ̏�����
	isHit_ = false;
	// �����蔻����󂯕t���Ȃ��׸ނ̏�����
	noAcceptHitFlag_ = false;
	// ���ݎv�l���Ă�����Ͳ�ޱ�ذ��ɰ��
	runningNode_ = nullptr;
	// ��Ͳ�ޱ�ް��̍쐬
	behaviorData_ = new BehaviorData;
}

Enemy::~Enemy()
{
}

void Enemy::Action(void)
{
	// ���̏�ɂ��鎞
	if (onFloor_)
	{
		// �����蔻��͉����Ȃ���
		if (!isHit_)
		{
			// ���݂̍s������Ͳ�ޱ�ذ��root���琄�_�������ʂ�ɰ�ނ��i�[
			runningNode_ = behaviorTree_->Inference(this,behaviorData_);
			// �i�[����s�����L���
			if (runningNode_ != nullptr)
			{
				// ��Ͳ�ޱ�ذ����ArunningNode_�ɑΉ�����ɰ�ނ𑖂点��
				behaviorTree_->Run(this, runningNode_, behaviorData_);
			}
			else
			{
				// �����s�������Ȃ��Ƃ���Idle��ݒ�
				SetAnimExcecuter(&Enemy::Idle);
			}
			// �s���ɉ�������Ұ��݂Ɠ������֐��߲���őJ�ڂ�����
			(this->*animExcecuter_)();
		}
		else
		{
			// �����ɓ����������͂�������Hit��Death�����
			(this->*stateExcecuter_)();
		}
	}

	// �U���̓����蔻��----------------------------------------------------------
	// player -> enemy
	if (!isHit_ && animExcecuter_ != &Enemy::Avoidance)
	{
		if (CollisionCheck()(colData_[1].first, player_->GetColliderBox(0).first))
		{
			isHit_ = true;
		}

	}

	// enemy -> player
	if (!player_->GetIsHit())
	{
		if (CollisionCheck()(colData_[0].first, player_->GetColliderBox(1).first))
		{
			player_->SetIsHit(true);
		}
	}
	//---------------------------------------------------------------------------

	// ��Ұ��݂̍X�V-------------------------------
	UpdateAnimation(currentAction_);
}

void Enemy::Move(void)
{
	// �����Ұ��݂ɕύX
	ChangeAction("Run");
	// �������ł����
	if (direction_ == Direction::Left)
	{
		speed_ = { -1.0f,0.0f,0.0f };
	}
	// �E�����ł����
	else
	{
		speed_ = { 1.0f,0.0f,0.0f };
	}
	// �ړ�����
	pos_ += speed_;
}

void Enemy::ZMove(void)
{
	// �����Ұ��݂ɕύX
	ChangeAction("Run");
	// ������Z���߼޼�݂̏��(�ʒu���)
	switch (zPosStatus_)
	{
		// ��ڲ԰������O�ɂ���ꍇ
	case ZPosFromPlayer::Minus:
		speed_ = { 0.0f,0.0f,-0.5f };
		break;
		// ��ڲ԰�������ɂ���ꍇ
	case ZPosFromPlayer::Plus:
		speed_ = { 0.0f,0.0f,0.5f };

		break;
		// ��v���Ă���ꍇ
	case ZPosFromPlayer::Non:
		speed_ = { 0.0f,0.0f,0.0f };

		break;
	default:
		break;
	}
	// Z���߼޼�݂̈ړ�����
	pos_.z += speed_.z;
}

void Enemy::Attack(void)
{
	// �ʏ�̍U���̏ꍇ
	if (attackFlag_)
	{
		// �ʏ�U���̱�Ұ��݂ɐ؂�ւ�
		ChangeAction("Attack");
		// ��Ұ��݂̏I��
		if (isAnimEnd_)
		{
			// �U���׸ނ�false
			attackFlag_ = false;
			// ����׸ނ�false
			avoidFromAttackFlag_ = false;
			// ��Ұ��݂�idle�ɐݒ�(default��)
			currentAction_ = "Idle";
		}
	}
	// ��ٍU���̏ꍇ
	if (skillAttackFlag_)
	{
		// ��ٍU���̃A�j���[�V�����ɐݒ�
		ChangeAction("SkillAttack");
		
		// ���ߖ��̽�ٍU��
		SkillAttack(myType_);
		// ��Ұ��ݏI����
		if (isAnimEnd_)
		{
			// ��ٍU���׸ނ�false
			skillAttackFlag_ = false;
			// ����׸ނ�false��
			avoidFromAttackFlag_ = false;
			// ��Ұ��݂�idle��(default)
			currentAction_ = "Idle";
		}
	}
}

void Enemy::SkillAttack(ENEMYTYPE type)
{
	// �G���߂ŕ���
	switch (type)
	{
	case ENEMYTYPE::CultistAssassin:
		// ��ٍU�������鎞�̱�Ұ��݊Ԋu
		if (animCnt_ >= 8.0f && animCnt_ <= 8.5f)
		{
			// �U���������Ȃ��׸ނ�true��
			noAcceptHitFlag_ = true;
			// ��ڲ԰�̌����߼޼�݂̎擾
			// ��ڲ԰�̌��ɉ���čU��������̂�
			pos_ = player_->GetBehindPos();
		}
		break;
	case ENEMYTYPE::Cultist:
		break;
	case ENEMYTYPE::TwistedCultist:
		break;
	case ENEMYTYPE::Max:
		break;
	default:
		break;
	}
}

void Enemy::Avoidance(void)
{
	// �U�������킷��Ұ��݂ɕύX
	ChangeAction("Avoidance");
	// ����s�����n�߂��ہAskill�Anormal�̍U���׸ނ͐܂�
	attackFlag_ = false;
	skillAttackFlag_ = false;
	// ����s���Ō��ɉ��������ݸ� >> ��Ұ��݂Ɠ������������̂�ϼޯ����ް�ɂ��Ă���
	if (animCnt_ >= 1.0f && animCnt_ <= 1.5f)
	{
		// ���ɉ�����\����߼޼��
		auto backPos = pos_;
		// ���������݌����Ă������
		switch (direction_)
		{
			// �E�����̏ꍇ
		case Direction::Right:
			backPos.x = backPos.x - 10.0f;
			break;
			// �������̏ꍇ
		case Direction::Left:
			backPos.x = backPos.x + 10.0f;
			break;
		case Direction::Max:
			break;
		default:
			break;
		}
		// �߼޼�݂̕ύX
		SetPosition(backPos);
	}
	// ��Ұ��ݏI����
	if (isAnimEnd_)
	{
		// ����s���̏I��
		avoidFromAttackFlag_ = false;
		// ����s�����I����idle�ɖ߂�
		animExcecuter_ = &Enemy::Idle;
	}
}

void Enemy::SetEnemy(ENEMYTYPE type,Vector3F pos)
{
	// �G���߾��
	myType_ = type;
	// �߼޼�ݾ��
	pos_ = pos;
	// �G�̐���
	Set(type);
}

void Enemy::SetBehavior(BehaviorTree* behaviorTree)
{
	// �G���߂ɉ�������Ͳ�ޱ�ذ�̾��
	behaviorTree_ = behaviorTree;
}

void Enemy::Set(ENEMYTYPE type)
{
	switch (type)
	{
	case ENEMYTYPE::CultistAssassin:
		// �G���̐ݒ�
		name_ = "Assassin_Cultist";
		// �G�̎��E�̐ݒ�
		visionRange_ = { 300.0f,50.0f };
		// Assassin�̏ꍇ�A��ق������Ă���
		hasSkill_ = true;
		break;
	case ENEMYTYPE::Cultist:
		// �G���ɐݒ�
		name_ = "Cultist";
		// �G�̎��E�̐ݒ�
		visionRange_ = { 300.0f,150.0f };
		// Cultist�̏ꍇ�ͽ�ق͎����Ȃ�
		hasSkill_ = false;
		break;
	case ENEMYTYPE::Max:
		break;
	default:
		break;
	}
	// ��Ұ��݂�������Ԃɂ���
	currentAction_ = "Idle";
	// ���s�ɻ��ނ̾��(���̻��ނ�Ă��Ȃ�����ڲ԰�̍U����������Ȃ����ɂȂ��Ă��܂�)
	// ������w�y���y���ȓG�x���o���Ă��܂�
	SetZSize(10);
	// �e�평����
	Actor::Initialize(name_);
}

const Vector3F& Enemy::GetDistance(void)
{
	// ��ڲ԰���߼޼��
	auto plPos = player_->GetPosition();
	// ��ڲ԰�Ƃ̋����𑪂��Ă���
	auto distance = plPos - pos_;

	// �����ɕ������ύX
	if (distance.x < 0.0f)
	{
		direction_ = Direction::Left;
	}
	else
	{
		direction_ = Direction::Right;
	}

	return distance;
}

// ���ޯ�ނ��s���ۂɎg�p����
void Enemy::DebugDraw(void)
{
	DrawFormatString(0, 50, 0xffffff, "enPos:(%f,%f,%f)", pos_.x, pos_.y, pos_.z);
	DrawFormatString(0, 100, 0xff0000, "enHP:%d", hp_);
}

// Z�߼޼�݂̏�Ԃ̾��
void Enemy::SetZPosStatus(ZPosFromPlayer zStatus)
{
	zPosStatus_ = zStatus;
}

void Enemy::SetAnimExcecuter(void(Enemy::* func)())
{
	// ��Ұ��ݏ�ԊǗ��֐��߲���̾��
	animExcecuter_ = func;
}

void Enemy::SetMoveType(MoveType moveType)
{
	// �ړ����߂̾��
	// ���s�ړ��Ȃ̂����ړ��Ȃ̂�
	moveType_ = moveType;
}
