#include "SkillAttackJudgement.h"
#include "../../Actor/Enemy.h"

bool SkillAttackJudgement::Judgement(Enemy* enemy)
{
    // skillAttackFlag��true�̏ꍇ�A���sɰ�ނɓn��
    if (enemy->GetSkillAttackFlag())
    {
        return true;
    }
    return false;
}
