#include "MoveLRJudgement.h"
#include "../../Actor/Enemy.h"

bool MoveLRJudgement::Judgement(Enemy* enemy)
{
	// ���ړ��\�ł���A�U�����Ă��Ȃ����true��Ԃ��āA���sɰ�ނɎ󂯓n��
	if (enemy->GetMoveType() == MoveType::MoveLR)
	{
		return true;
	}
	return false;
}
