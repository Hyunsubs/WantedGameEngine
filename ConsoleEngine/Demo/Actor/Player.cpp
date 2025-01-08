#include "Player.h"
#include "Engine/Engine.h"

Player::Player(char image)
	: Super(image)
{
}


void Player::Update(float deltaTime)
{
	// �θ� �Լ� ȣ��
	Super::Update(deltaTime);

	if (Engine::Get().GetKey(VK_LEFT))
	{
		// �� ��ġ ���
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
		// �� ��ġ ���
		Vector2 newPosition = position;
		++newPosition.x;
		if (newPosition.x > 100)
		{
			newPosition.x = 100;
		}
		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_UP))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		--newPosition.y;
		if (newPosition.y < 0)
		{
			newPosition.y = 0;
		}
		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_DOWN))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		++newPosition.y;
		if (newPosition.y > 20)
		{
			newPosition.y = 20;
		}
		SetPosition(newPosition);
	}

	


}

