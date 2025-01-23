#include "Enemy.h"
#include "Engine/Engine.h"
#include "Actor/EnemyBullet.h"

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

	// 화면 밖 벗어나면 삭제
	if (xPosition < 0.f || position.x >= Engine::Get().ScreenSize().x - width)
	{
		Destroy();
	}

	// 탄약 발사
	static float elapsedTime = 0.f;
	static float fireInterval = RandomPercent(1.f, 2.f);

	elapsedTime += deltaTime;

	// 타이머 처리
	if (elapsedTime < fireInterval)
	{
		return;
	}

	// 타이머 초기화
	elapsedTime = 0.f;
	fireInterval = RandomPercent(1.f, 2.f);

	// 탄약 생성
	Engine::Get().AddActor(
		new EnemyBullet(Vector2(position.x + width / 2, position.y))
	);

}
