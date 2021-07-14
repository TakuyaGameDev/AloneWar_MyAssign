#include "AttackJudgement.h"
#include "../../Actor/Enemy.h"

bool AttackJudgement::Judgement(Enemy* enemy)
{
    // �U�����Ă���Έړ��͂����Ȃ�
    if (enemy->GetAttackFlag() || enemy->GetSkillAttackFlag())
    {
        return true;
    }
    // ��ڲ԰�Ƃ̋����𑪂�
    auto distance = enemy->GetDistance();

    // �ʏ�U��
    if ((abs(distance.x) <= enemy->GetVisionRange().attackRange_) && (abs(distance.z) <= 5.0f))
    {
        // �ʏ�U����true�ɂ���
        enemy->SetAttackFlag(true);
        // skillAttack��false�ɂ���
        enemy->SetSkillAttackFlag(false);
        return true;
    }

    // skillAttack�U��
    // ��ق������Ă����
    if (enemy->HasSkill())
    {
        if ((abs(distance.x) <= enemy->GetVisionRange().attackRange_ + 50.0f) && (abs(distance.z) <= 5.0f))
        {
            // skillAttack��true��
            enemy->SetSkillAttackFlag(true);
            // �ʏ�̍U����false��
            enemy->SetAttackFlag(false);
            return true;
        }
    }

    // ���ɂ����Ă͂܂�Ȃ���΂ǂ����false�ɂ���
    enemy->SetAttackFlag(false);
    enemy->SetSkillAttackFlag(false);

    return false;
}
