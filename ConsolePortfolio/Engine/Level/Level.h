#pragma once

#include "Core.h"
#include "RTTI.h"
#include <vector>

// ���� ����(Forward Declaration).
class Actor;
class ENGINE_API Level : public RTTI
{
	// RTTI ����.
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// ���� �߰� �Լ�.
	void AddActor(Actor* newActor);

	// ���� ��û�� �� ���͸� �����ϴ� �Լ�.
	//void DestroyActor();
	void ProcessAddedAndDestroyedActor();

	// �ʱ�ȭ �Լ�(ó�� �����Ұ͵�)
	virtual void Init();

	std::vector<Actor*>& GetActorList() { return actors; }

	// ���� ó�� �Լ�.
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ���� ������ ��ġ�Ǵ� ��ü(����) �迭.
	std::vector<Actor*> actors;
	std::vector<Actor*> requestedActor;

	// �߰� ��û�� ����.
	Actor* addRequestedActor = nullptr;

};