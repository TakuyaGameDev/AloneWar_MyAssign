#include "BehaviorData.h"
#include "BehaviorTree.h"
#include "ActionNode.h"

BehaviorData::BehaviorData()
{
	// ��Ͳ�ޱ�ް��̏�����
	Init();
}

BehaviorData::~BehaviorData()
{
}

void BehaviorData::Init(void)
{
	runSequenceStepMap_.clear();
	while (sequenceStack_.size() > 0)
	{
		sequenceStack_.pop();
	}
}

void BehaviorData::PushSequenceNode(ActionNode* node)
{
	sequenceStack_.push(node);
}

ActionNode* BehaviorData::PopSequenceNode(void)
{
	// ���g���Ȃ��Ȃ�nullptr��Ԃ�
	if (sequenceStack_.empty())
	{
		return nullptr;
	}
	ActionNode* node = sequenceStack_.top();

	// ���o�����ް���nullptr�łȂ����
	if (node != nullptr)
	{
		// ���o�����ް����폜
		sequenceStack_.pop();
	}

	return node;
}

bool BehaviorData::IsUsedNode(std::string nodeName)
{
	// �g�p���Ă��Ȃ�������false
	if (usedNodeMap_.count(nodeName) == 0)
	{
		return false;
	}
	// �g�p���Ă����炻��ɰ�ނ�Ԃ�
	return usedNodeMap_[nodeName];
}

void BehaviorData::EntryUsedNode(std::string nodeName)
{
	// �g�p���Ă���Ƃ����׸ނ𗧂Ă�
	usedNodeMap_[nodeName] = true;
}

int BehaviorData::GetSequenceStep(std::string nodeName)
{
	// �����݂̍s���ï�߂̎擾
	if (runSequenceStepMap_.count(nodeName) == 0)
	{
		// �ï�߂��ذ�̎n�_�̏ꍇ0�ɾ�Ă���
		runSequenceStepMap_[nodeName] = 0;
	}
	return runSequenceStepMap_[nodeName];
}

void BehaviorData::SetSequenceStep(std::string nodeName,int step)
{
	// �v�l�ï�߂̾��
	runSequenceStepMap_[nodeName] = step;
}

void BehaviorData::ResetNodeUsed(std::vector<ActionNode*>* resetHieralchy)
{
	// ɰ�ނ��g�p���Ă����׸ނ�ؾ��
	for (auto itr = resetHieralchy->begin(); itr != resetHieralchy->end(); itr++)
	{
		usedNodeMap_[(*itr)->GetNodeName()] = false;
	}
}
