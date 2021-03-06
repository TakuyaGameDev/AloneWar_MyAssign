#include "MoveLRJudgement.h"
#include "../../Actor/Enemy.h"

bool MoveLRJudgement::Judgement(Enemy* enemy)
{
	// 横移動可能であり、攻撃していなければtrueを返して、実行ﾉｰﾄﾞに受け渡す
	if (enemy->GetMoveType() == MoveType::MoveLR)
	{
		return true;
	}
	return false;
}
