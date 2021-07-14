#include "ActionNode.h"
#include "Judgement/JudgementBase.h"
#include "Action/ActionBase.h"
#include "BehaviorData.h"

ActionNode::ActionNode(std::string nodeName, ActionNode* parent, 
	ActionNode* sibling,int priority, BehaviorTree::SelectRule rule,
	JudgementBase* judgement, ActionBase* action):
	nodeName_(nodeName),parent_(parent),
	sibling_(sibling),priority_(priority),
	selectRule_(rule),judgement_(judgement),
	action_(action),child_(NULL)
{
}

ActionNode* ActionNode::Inference(Enemy* enemy,BehaviorData* data)
{
	// ���sɰ�ފi�[�p
	ActionNode* result = nullptr;

	for (int i = 0; i < child_.size(); i++)
	{
		if (child_[i]->judgement_ != nullptr)
		{
			// ���肪true�ɂȂ�������sɰ�ފi�[�p�ϐ��Ɋi�[
			if (child_[i]->Judgement(enemy))
			{
				result = child_[i];
			}
		}
	}

	if (result != nullptr)
	{
		// ���s�ް��������Ă���ΏI��
		if (result->HasAction())
		{
			return result;
		}
		else
		{
			// �����Ă��Ȃ���ΐ��_���s
			result = result->Inference(enemy,data);
		}
	}

	return result;
}

ActionNode* ActionNode::SearchActionNode(std::string nodeName)
{
	if (nodeName_ == nodeName)
	{
		return this;
	}
	else
	{
		// �qɰ�ނŌ���
		for (auto itr = child_.begin(); itr != child_.end(); itr++)
		{
			ActionNode* node = (*itr)->SearchActionNode(nodeName);
			if (node != nullptr)
			{
				return node;
			}
		}
	}
	return nullptr;
}

void ActionNode::AddChild(ActionNode* childNode)
{
	child_.push_back(childNode);
}

ActionNode* ActionNode::GetLastChild(void)
{
	if (child_.size() == 0)
	{
		return nullptr;
	}

	return child_[child_.size() - 1];
}

bool ActionNode::Judgement(Enemy* enemy)
{
	// �s���̔���
	if (judgement_ != nullptr)
	{
		return judgement_->operator()(enemy);
	}
	return true;
}

bool ActionNode::HasAction(void)
{
	// ���sɰ�ނ������Ă����true
	return action_ != nullptr?true:false;
}

void ActionNode::Run(Enemy* enemy)
{
	// �s���̎��s
	if (action_ != nullptr)
	{
		action_->operator()(enemy);
	}
}
