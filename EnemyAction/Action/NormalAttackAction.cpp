#include "../../EnemyAction/Action/NormalAttackAction.h"
#include "../../Actor/Enemy.h"

void NormalAttackAction::Run(Enemy* enemy)
{
	// ��Ұ��ݏ�Ԃ�Attack��ԂɕύX
	enemy->SetAnimExcecuter(&Enemy::Attack);
}
