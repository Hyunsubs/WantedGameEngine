#include "PreCompiledHeader/PreCompiledHeader.h"
#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Actor/Player.h"

TestLevel::TestLevel()
{
	Player* player = new Player();
	AddActor(player);
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}
