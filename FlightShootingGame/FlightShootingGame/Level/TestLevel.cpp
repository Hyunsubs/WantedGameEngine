#include "PreCompiledHeader/PreCompiledHeader.h"
#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"

TestLevel::TestLevel()
{
	Player* player = new Player("jet");
	AddActor(player);
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 예외처리
	if (deltaTime > 1.f)
	{
		return;
	}

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// 적생성
	static float elapsedTime = 0.f;
	static float spawnTime = RandomPercent(1.f, 3.f);

	// 타이머
	elapsedTime += deltaTime;
	if (elapsedTime < spawnTime)
	{
		return;
	}

	// 타이머 리셋
	elapsedTime = 0.f;
	spawnTime = RandomPercent(1.f, 3.f);

	// 적생성
	Enemy* pEnemy = new Enemy("e", Random(1, 10));
	AddActor(pEnemy);
}
