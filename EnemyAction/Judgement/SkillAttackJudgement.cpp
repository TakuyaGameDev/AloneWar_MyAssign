#include "SkillAttackJudgement.h"
#include "../../Actor/Enemy.h"

bool SkillAttackJudgement::Judgement(Enemy* enemy)
{
    // skillAttackFlagがtrueの場合、実行ﾉｰﾄﾞに渡す
    if (enemy->GetSkillAttackFlag())
    {
        return true;
    }
    return false;
}
