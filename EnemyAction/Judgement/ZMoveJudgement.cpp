#include "ZMoveJudgement.h"
#include "../../Actor/Enemy.h"

bool ZMoveJudgement::Judgement(Enemy* enemy)
{
	// ���ړ��\�ł���A�U�����Ă��Ȃ����true��Ԃ��āA���sɰ�ނɎ󂯓n��
	if (enemy->GetMoveType() == MoveType::MoveZ)
	{
		return true;
	}
	return false;
}
