#include "AvoidanceJudgement.h"
#include "../../Actor/Enemy.h"
#include "../../Actor/Player.h"

bool AvoidanceJudgement::Judgement(Enemy* enemy)
{
    // ����avoidance�s�����s���Ȃ��
    if (enemy->GetAnimExcecuter() == &Enemy::Avoidance)
    {
        return true;
    }
    // ��ڲ԰�Ƃ̋����𑪂�
    auto distance = enemy->GetDistance();
    auto pl = enemy->GetPlayer();
    // ��ڲ԰���^���ʂɂ��邩�ǂ������׸�
    bool plIsNear = false;

    if ((abs(distance.x) <= 50.0f) &&
        (abs(distance.y) <= 0.0f) &&
        (abs(distance.z) <= 5.0f))
    {
        plIsNear = true;
    }
    // ��ڲ԰���^���ʂɂ���
    if (plIsNear)
    {
        // ��ڲ԰���U�����Ă�����
        if (pl->GetAttackFlag() && !enemy->GetAvoidFlag())
        {
            int random = 0;
            // HP��80%�ȏ�̎�
            if (enemy->IsHPPercentOver(80))
            {
                random = 20;
            }
            // HP��50%�ȏ�̎�
            else if (enemy->IsHPPercentOver(50))
            {
                random = 50;
            }
            // HP��30%�ȏ�̎�
            else if (enemy->IsHPPercentOver(30))
            {
                random = 65;
            }
            // HP��30%�ȉ��̎�
            else
            {
                random = 70;
            }
            // ����s���׸ނ�true�ɂ���
            // 1�񂵂�����Ăق����Ȃ�����
            // ���������Ă�����100%����s�������Ă��܂�
            // ����ђl�𐶐�������ɉ���׸ނ�true�ɂ���
            enemy->SetAvoidFlag(true);
            // ����тɉ���s��������
            if (rand() % 100 <= random)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }

    return false;
}
