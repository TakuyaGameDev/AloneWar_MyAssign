#pragma once

class Enemy;

// �s���׽�̐e�׽
struct ActionBase
{
public:

	// ���s
	void operator()(Enemy* enemy)
	{
		Run(enemy);
	}
	// �������z�ŵ��ްײ��
	virtual void Run(Enemy* enemy) = 0;

protected:

};

