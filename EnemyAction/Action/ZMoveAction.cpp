#include "../../EnemyAction/Action/ZMoveAction.h"
#include "../../Actor/Enemy.h"

void ZMoveAction::Run(Enemy* enemy)
{
	// ����MoveZ��Ԃ��Ɖ������Ȃ�
	if (enemy->GetMoveType() != MoveType::MoveZ)
	{
		return;
	}
	// ��Ұ��ݏ�Ԃ�ZMove�ɕύX
	enemy->SetAnimExcecuter(&Enemy::ZMove);
}
