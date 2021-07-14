#pragma once

#include <string>

struct JudgementBase;
class BehaviorData;
struct ActionBase;
class Enemy;
class ActionNode;
// �v�lٰ�݂̖��ް��׽
class BehaviorTree
{
public:
	// �I�����[��
	enum SelectRule
	{
		Non,
		// �D�揇��
		Priority,			
		// ���ݽ
		Sequence,			
		// ���ݼ��ٰ��ݸ�
		SequencialLooping,	
		// �����
		Random,				
		// �݁E��
		On_Off,
	};

	BehaviorTree();
	~BehaviorTree();
	// behaiviorTree�ւ�ɰ�ނ̒ǉ�
	void AddNode(std::string searchName, std::string entryName,int priority,SelectRule selectRule, JudgementBase* judgement, ActionBase* action);
	// ɰ�ނ̐��_
	ActionNode* Inference(Enemy* enemy,BehaviorData* data);
	// ���ݽɰ�ނ��琄�_
	ActionNode* SequenceInference(ActionNode* sequenceNode, Enemy* enemy, BehaviorData* data);
	// ���s
	void Run(Enemy* enemy,ActionNode* actionNode,BehaviorData* data);
private:
	// ٰ�(ɰ�ނ̈�ԍŏ�)
	ActionNode* root_;
};

