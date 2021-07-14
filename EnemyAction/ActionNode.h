#pragma once
#include <list>
#include <map>
#include <string>
#include <vector>

#include "Judgement/JudgementBase.h"
#include "Action/ActionBase.h"
#include "BehaviorTree.h"

// �D��x���Ƃ肠������ԏ��������ɂ��Ă���
#define DefPriority -100000

class Enemy;
class ActionNode;
class BehaviorData;

// ��Ͳ�ޱɰ��(�v�lɰ��)�׽
class ActionNode
{
public:
	// param@ nodeName:��Ă���ɰ�ޖ�
	// param@ parent:�e�ƂȂ�ɰ��
	// param@ sibling:�Z��ƂȂ�ɰ��
	// param@ priority:�D��x
	// param@ rule:�ذ����v�lɰ�ނ��I�������ۂ̑I����ƂȂ�ٰ�
	// param@ judgement:�s���̔���
	// param@ action:�s�����s
	ActionNode(std::string nodeName,ActionNode* parent,ActionNode* sibling,int priority,BehaviorTree::SelectRule rule,JudgementBase* judgement,ActionBase* action);
	// ɰ�ސ��_
	ActionNode* Inference(Enemy* enemy,BehaviorData* data);
	// ɰ�ނ̑{��
	ActionNode* SearchActionNode(std::string nodeName);
	// �����̎q���ɒǉ�
	void AddChild(ActionNode* childNode);
	// �������擾
	ActionNode* GetLastChild(void);
	// ����
	bool Judgement(Enemy* enemy);
	// �D��x�̎擾
	const int& GetPriority(void)
	{
		return priority_;
	}
	// ���s�ް��������Ă��邩
	bool HasAction(void);
	// ���s
	void Run(Enemy* enemy);

	// ɰ��Ȱт̎擾
	std::string GetNodeName(void)
	{
		return nodeName_;
	}

private:

protected:
	// ɰ�ނ̖��O
	std::string nodeName_;
	// �����̎qɰ��
	std::vector<ActionNode*> child_;
	// �����̐eɰ��
	ActionNode* parent_;
	// �����̌Z��ɰ��
	ActionNode* sibling_;
	// ���sɰ��
	ActionBase* action_;
	// ����ɰ��
	JudgementBase* judgement_;
	// �I��@
	BehaviorTree::SelectRule selectRule_;
	// �D��x
	int priority_;
};

