#include "SkillAttackAction.h"
#include "../../Actor/Enemy.h"

void SkillAttackAction::Run(Enemy* enemy)
{
	// ��Ұ��ݏ�Ԃ�Attack��ԂɕύX
	enemy->SetAnimExcecuter(&Enemy::Attack);
}
