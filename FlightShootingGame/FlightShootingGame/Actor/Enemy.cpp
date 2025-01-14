#include "Enemy.h"
#include "Engine/Engine.h"

Enemy::Enemy(const char* image, int yPosition)
	: DrawableActor(image)
{

	// 랜덤으로 이동할 방향 선택
	int random = Random(1, 10);
	if (random % 2 == 0)
	{
		xPosition = (float)Engine::Get().ScreenSize().x - width;
		direction = Direction::Left;
	}
	else
	{
		xPosition = 0.f;
		direction = Direction::Right;
	}


	this->position = Vector2((int)xPosition, yPosition);
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	float factor = direction == Direction::Left ? -1.f : 1.f;
	xPosition += speed * factor * deltaTime;
	position.x = (int)xPosition;

	if (xPosition < 0.f || position.x >= Engine::Get().ScreenSize().x - width)
	{
		Destroy();
	}

}
