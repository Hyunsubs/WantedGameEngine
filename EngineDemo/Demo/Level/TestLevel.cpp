#include "TestLevel.h"
#include "Engine/Engine.h"
#include <windows.h>

TestLevel::TestLevel()
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}
