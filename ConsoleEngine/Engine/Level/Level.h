#pragma once
#include "Container/List.h"
#include "RTTI.h"

class Actor;
class ENGINE_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�
	void AddActor(Actor* newActor);

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭
	List<Actor*> actors;
};

