#include "NormalAttackJudgement.h"
#include "../../Actor/Enemy.h"

bool NormalAttackJudgement::Judgement(Enemy* enemy)
{
    // �ʏ�U�����׸ނ�true�̏ꍇtrue��Ԃ��A���sɰ�ނɓn��
    if (enemy->GetAttackFlag())
    {
        return true;
    }
    return false;
}
