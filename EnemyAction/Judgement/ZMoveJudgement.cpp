#include "ZMoveJudgement.h"
#include "../../Actor/Enemy.h"

bool ZMoveJudgement::Judgement(Enemy* enemy)
{
	// 奥移動可能であり、攻撃していなければtrueを返して、実行ﾉｰﾄﾞに受け渡す
	if (enemy->GetMoveType() == MoveType::MoveZ)
	{
		return true;
	}
	return false;
}
