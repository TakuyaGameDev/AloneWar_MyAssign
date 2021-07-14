#include "MoveJudgement.h"
#include "../../Actor/Enemy.h"

bool MoveJudgement::Judgement(Enemy* enemy)
{
	// �U�����Ă��鎞�͓������Ȃ�
	if (enemy->GetAttackFlag() || enemy->GetSkillAttackFlag())
	{
		return false;
	}
	// ��ڲ԰�Ƃ̋����𑪂�
	auto dis = enemy->GetDistance();
	// ���s�ړ�
	if (abs(dis.x) > enemy->GetVisionRange().attackRange_)
	{
		enemy->SetMoveType(MoveType::MoveLR);
		return true;
	}
	// Z���̏�Ԃ����Ă���
	if (abs(dis.x) <= enemy->GetVisionRange().attackRange_)
	{
		// Z���̏��
		// ��ڲ԰������O�ɂ���ꍇ
		if (dis.z < 0.0f)
		{
			enemy->SetZPosStatus(ZPosFromPlayer::Minus);
			enemy->SetMoveType(MoveType::MoveZ);
			return true;
		}
		// Z���̏��
		// ��ڲ԰�������ɂ���ꍇ
		if (dis.z > 0.0f)
		{
			enemy->SetZPosStatus(ZPosFromPlayer::Plus);
			enemy->SetMoveType(MoveType::MoveZ);
			return true;
		}
	}
	// ���ɂ����Ă͂܂�Ȃ��ꍇMoveType��Non(�����Ă��Ȃ����)��
	enemy->SetMoveType(MoveType::Non);

    return false;
}
