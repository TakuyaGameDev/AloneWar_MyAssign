#pragma once
#include <memory>
#include <vector>

// �ޯ̧�e�׽
class ObjectPool
{
public:
	ObjectPool() {};
	virtual ~ObjectPool() {};
	// pool�̔j��
	virtual void Destroy(void) = 0;
	// pool�̍X�V
	virtual void Update(void) = 0;
	// pool�̒��g�̐l�����̕`��
	virtual void Draw(void) = 0;
private:

protected:
	// pool�̻���
	int poolSize_;
};