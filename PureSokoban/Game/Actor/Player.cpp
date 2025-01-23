#include "Player.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

Player::Player(const Vector2& position, GameLevel* level)
	: DrawableActor("P"), refLevel(level)
{
	// ��ġ ����.
	this->position = position;

	// ���� ����.
	color = Color::White;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// ESC ����.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		/*Engine::Get().QuitGame();*/
		// �޴� ���
		Game::Get().ToggleMenu();
	}

	// �����¿�.
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(
			Vector2(position.x - 1, position.y))
			)
		{
			position.x -= 1;
		}

	}

	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(
			Vector2(position.x + 1, position.y))
			)
		{
			position.x += 1;
		}
	}

	if (Engine::Get().GetKeyDown(VK_UP))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(
			Vector2(position.x, position.y - 1))
			)
		{
			position.y -= 1;
		}
	}

	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		// �̵� �������� Ȯ��
		if (refLevel->CanPlayerMove(
			Vector2(position.x, position.y + 1))
			)
		{
			position.y += 1;
		}
	}
}