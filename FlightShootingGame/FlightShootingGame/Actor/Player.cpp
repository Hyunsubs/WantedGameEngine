#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"
#include "PlayerBullet.h"

Player::Player(const char* image)
	: Super(image)
{
	//position = Vector2(0, 20);
	position = Vector2(Engine::Get().ScreenSize().x / 2, Engine::Get().ScreenSize().y - 1);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	shoot_time -= deltaTime;
	if (shoot_time <= 0.f)
		shoot_time = 0.f;

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
		if (newPosition.x > Engine::Get().ScreenSize().x - width)
		{
			newPosition.x = Engine::Get().ScreenSize().x - width;
		}

		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_SPACE) && shoot_time <= 0.f)
	{
		PlayerBullet* bullet = new PlayerBullet(Vector2(position.x + (width / 2), position.y));
		shoot_time = 0.1f;
		Engine::Get().AddActor(bullet);
	}
}