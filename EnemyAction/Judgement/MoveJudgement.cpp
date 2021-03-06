#include "MoveJudgement.h"
#include "../../Actor/Enemy.h"

bool MoveJudgement::Judgement(Enemy* enemy)
{
	// 攻撃している時は動かさない
	if (enemy->GetAttackFlag() || enemy->GetSkillAttackFlag())
	{
		return false;
	}
	// ﾌﾟﾚｲﾔｰとの距離を測る
	auto dis = enemy->GetDistance();
	// 奥行移動
	if (abs(dis.x) > enemy->GetVisionRange().attackRange_)
	{
		enemy->SetMoveType(MoveType::MoveLR);
		return true;
	}
	// Z軸の状態を見ている
	if (abs(dis.x) <= enemy->GetVisionRange().attackRange_)
	{
		// Z軸の状態
		// ﾌﾟﾚｲﾔｰよりも手前にいる場合
		if (dis.z < 0.0f)
		{
			enemy->SetZPosStatus(ZPosFromPlayer::Minus);
			enemy->SetMoveType(MoveType::MoveZ);
			return true;
		}
		// Z軸の状態
		// ﾌﾟﾚｲﾔｰよりも奥にいる場合
		if (dis.z > 0.0f)
		{
			enemy->SetZPosStatus(ZPosFromPlayer::Plus);
			enemy->SetMoveType(MoveType::MoveZ);
			return true;
		}
	}
	// 何にも当てはまらない場合MoveTypeをNon(動いていない状態)に
	enemy->SetMoveType(MoveType::Non);

    return false;
}
