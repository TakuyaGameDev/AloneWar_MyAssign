#include "AvoidanceAction.h"
#include "../../Actor/Enemy.h"

void AvoidanceAction::Run(Enemy* enemy)
{
	// ��Ұ��ݏ�Ԃ��U������s����ԂɕύX
	enemy->SetAnimExcecuter(&Enemy::Avoidance);
}
