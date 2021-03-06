#include "AttackJudgement.h"
#include "../../Actor/Enemy.h"

bool AttackJudgement::Judgement(Enemy* enemy)
{
    // 攻撃していれば移動はさせない
    if (enemy->GetAttackFlag() || enemy->GetSkillAttackFlag())
    {
        return true;
    }
    // ﾌﾟﾚｲﾔｰとの距離を測る
    auto distance = enemy->GetDistance();

    // 通常攻撃
    if ((abs(distance.x) <= enemy->GetVisionRange().attackRange_) && (abs(distance.z) <= 5.0f))
    {
        // 通常攻撃をtrueにする
        enemy->SetAttackFlag(true);
        // skillAttackをfalseにする
        enemy->SetSkillAttackFlag(false);
        return true;
    }

    // skillAttack攻撃
    // ｽｷﾙを持っていれば
    if (enemy->HasSkill())
    {
        if ((abs(distance.x) <= enemy->GetVisionRange().attackRange_ + 50.0f) && (abs(distance.z) <= 5.0f))
        {
            // skillAttackをtrueに
            enemy->SetSkillAttackFlag(true);
            // 通常の攻撃をfalseに
            enemy->SetAttackFlag(false);
            return true;
        }
    }

    // 何にも当てはまらなければどちらもfalseにする
    enemy->SetAttackFlag(false);
    enemy->SetSkillAttackFlag(false);

    return false;
}
