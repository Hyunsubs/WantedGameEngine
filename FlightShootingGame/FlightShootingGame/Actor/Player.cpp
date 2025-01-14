#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

Player::Player(const char* image)
	: Super(image)
{
	position = Vector2(0, 18);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKey(VK_LEFT))
	{
		Vector2 newPosition = position;
		--newPosition.x;
		if (newPosition.x < 0)
		{
			newPosition.x = 0;
		}

		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		Vector2 newPosition = position;
		++newPosition.x;
		if (newPosition.x > 28)
		{
			newPosition.x = 28;
		}

		SetPosition(newPosition);
	}
}