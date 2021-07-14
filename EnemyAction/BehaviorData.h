#pragma once

#include <vector>
#include <stack>
#include <map>
#include <string>

class ActionNode;
class Enemy;

// ��Ͳ�ޱ�ذ�ް�
class BehaviorData
{
public:
	BehaviorData();
	~BehaviorData();
	// ��Ͳ�ޱ�ް��̏�����
	void Init(void);
	// ���ݽɰ�ނ��߯��
	void PushSequenceNode(ActionNode* node);
	// ���ݽɰ�ނ��߯��
	// ���g�̎��o��
	ActionNode* PopSequenceNode(void);
	// ɰ�ނ̎g�p����
	bool IsUsedNode(std::string nodeName);
	// �g�p�ς�ɰ�ނɓo�^
	void EntryUsedNode(std::string nodeName);
	// ���ݽ�ï�߂̎擾
	int GetSequenceStep(std::string nodeName);
	// ���ݽ�ï�߂̾��
	void SetSequenceStep(std::string nodeName, int step);
	// �g�p�ς�ɰ�ނ�ؾ��
	void ResetNodeUsed(std::vector<ActionNode*>* resetHieralchy);
private:
	// ���ݽɰ�޽���
	std::stack<ActionNode*> sequenceStack_;
	// ���s���ݽ�̽ï��ϯ��
	std::map<std::string, int> runSequenceStepMap_;
	// ɰ�ނ̎g�p����ϯ��
	std::map<std::string, bool> usedNodeMap_;
};

