#include "SkillAttackAction.h"
#include "../../Actor/Enemy.h"

void SkillAttackAction::Run(Enemy* enemy)
{
	// ｱﾆﾒｰｼｮﾝ状態をAttack状態に変更
	enemy->SetAnimExcecuter(&Enemy::Attack);
}
