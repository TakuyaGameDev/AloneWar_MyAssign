#pragma once

class Enemy;
// ����׽�̐e�׽
struct JudgementBase
{
public:

	bool operator()(Enemy* enemy)
	{
		return Judgement(enemy);
	}
private:
	virtual bool Judgement(Enemy* enemy) = 0;

};

