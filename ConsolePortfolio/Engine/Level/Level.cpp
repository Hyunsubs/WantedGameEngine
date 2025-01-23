#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"
#include "Actor/BoundingBox.h"
#include "Engine/Engine.h"

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����.
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	requestedActor.push_back(newActor);
}


void Level::ProcessAddedAndDestroyedActor()
{
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��.
	for (int ix = 0; ix < actors.size();)
	{
		if (actors[ix]->isExpired)
		{
			delete actors[ix];
			actors[ix] = nullptr;
			actors.erase(actors.begin() + ix);
			continue;
		}
		++ix;
	}

	// �߰� ��û�� ���� ó��.
	for (auto& actor: requestedActor)
	{
		actors.push_back(actor);
	}

	requestedActor.clear();
}

void Level::Init()
{
	for (Actor* actor : actors)
	{
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Init();
	}
}

void Level::Update(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��.
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�.
		if (actor == nullptr)
			continue;

		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	if (Engine::Get().GetPrintCollision())
	{
		std::vector<Actor*> boundingBoxes = {};
		// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��.
		for (Actor* actor : actors)
		{
			// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�.
			if (!actor->isActive || actor->isExpired)
			{
				continue;
			}
			else if (actor->As<BoundingBox>())
			{
				boundingBoxes.push_back(actor);
				continue;
			}
			actor->Draw();
		}

		for (int i = 0; i < boundingBoxes.size(); i++)
		{
			boundingBoxes[i]->Draw();
		}
	}

	else
	{
		// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��.
		for (Actor* actor : actors)
		{
			// �ٿ�� �ڽ��� ��� ����Ʈ ���� ����
			if (actor->As<BoundingBox>())
			{
				continue;
			}
			// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�.
			if (!actor->isActive || actor->isExpired)
			{
				continue;
			}
			actor->Draw();
		}
	}

}