#include "BehaviorTree.h"
#include "BehaviorData.h"
#include "ActionNode.h"
#include "Judgement/JudgementBase.h"
#include "Action/ActionBase.h"

BehaviorTree::BehaviorTree()
{
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::AddNode(std::string searchName, std::string entryName,int priority, SelectRule selectRule, JudgementBase* judgement, ActionBase* action)
{
	// searchName�̕����񂪋󂾂�
	if (searchName.size() != 0)
	{
		// �܂��eɰ�ނ�T��
		ActionNode* searchNode = root_->SearchActionNode(searchName);
		// �e�������
		if (searchNode != nullptr)
		{
			// �����̎q����T��
			ActionNode* sibling = searchNode->GetLastChild();
			// �ǉ�����ɰ�ނ̍쐬
			ActionNode* addNode = new ActionNode(entryName, searchNode, sibling,priority,selectRule, judgement, action);
			// ɰ�ނ̒ǉ�
			searchNode->AddChild(addNode);
		}
	}
	else
	{
		// ��������ٰĂ��Ȃ����
		if (root_ == nullptr)
		{
			// ٰĂ̍쐬
			// child��sibling�͋���nullptr(���M���e�Ȃ̂�)
			root_ = new ActionNode(entryName, nullptr, nullptr,priority,selectRule, judgement, action);
		}
		else
		{
			// ���Ă�������
			_ASSERT("root is already registered!!");
		}
	}
}

ActionNode* BehaviorTree::Inference(Enemy* enemy,BehaviorData* data)
{
	// ɰ�ސ��_
	return root_->Inference(enemy,data);
}

ActionNode* BehaviorTree::SequenceInference(ActionNode* sequenceNode, Enemy* enemy, BehaviorData* data)
{
	// ɰ�ސ��_�����Đ��_�������ʁA�s���\��ɰ�ނ�Ԃ�
	return sequenceNode->Inference(enemy,data);
}

void BehaviorTree::Run(Enemy* enemy, ActionNode* actionNode,BehaviorData* data)
{
	// ɰ�ނ̎��s
	actionNode->Run(enemy);
}
