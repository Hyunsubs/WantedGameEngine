#pragma once
#include "PreCompiledHeader.h"

class Actor;
class ENGINE_API Level
{
public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�
	void AddActor(Actor* newActor);

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭
	Actor** actors;

	// ������ �� �ִ� ������ ũ��
	int capacity;

	// ������ ��
	int count;
};
