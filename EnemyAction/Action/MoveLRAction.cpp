#include "../../EnemyAction/Action/MoveLRAction.h"
#include "../../Actor/Enemy.h"

void MoveLRAction::Run(Enemy* enemy)
{
	// ����MoveLR��Ԃ��Ɖ������Ȃ�
	if (enemy->GetMoveType() != MoveType::MoveLR)
	{
		return;
	}
	// ��Ұ��ݏ�Ԃ�Move��ԂɕύX
	enemy->SetAnimExcecuter(&Enemy::Move);
}
