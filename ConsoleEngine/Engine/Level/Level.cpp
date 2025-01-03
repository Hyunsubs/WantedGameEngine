#include "PreCompiledHeader.h"
#include "Level.h"
#include "../Actor/Actor.h"

Level::Level()
	: actors(nullptr)
	, capacity(4)
	, count(0)
{
	// ���� �迭 ����
	actors = new Actor*[capacity];
	memset(actors, 0, sizeof(size_t) * capacity);
}

Level::~Level()
{
	// ���� ����
	for (int i = 0; i < count; i++)
	{
		delete actors[i];
		actors[i] = nullptr;
	}

	// ���� �迭 ����
	delete[] actors;
	actors = nullptr;
}

void Level::AddActor(Actor* newActor)
{
	// ���� �Ҵ�� ������ ������� Ȯ��
	if (count == capacity)
	{
		// ���� �߰� �Ҵ�
		int newCapacity = capacity * 2;

		// �ӽ� ����
		Actor** temp = new Actor * [newCapacity];

		// ���� �� ����
		memcpy(temp, actors, sizeof(size_t) * capacity);

		// ���� �迭 ����
		delete[] actors;

		// �迭 ��ü
		actors = temp;

		// ũ�� ����
		capacity = newCapacity;
	}

	// ���� �߰�
	actors[count] = new Actor;
	++count;
}

void Level::Update(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��
	for (int i = 0; i < count; i++)
	{
		actors[i]->Update(deltaTime);
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��
	for (int i = 0; i < count; i++)
	{
		actors[i]->Draw();
	}
}
