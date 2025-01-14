#include "PlayerBullet.h"
#include "Engine/Engine.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	: DrawableActor("!")
{
	// 탄약 위치 설정
	this->position = position;
	yPosition = (float)position.y;
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 위치 갱신
	yPosition -= speed * deltaTime;
	position.y = (int)yPosition;

	// y 좌표가 화면을 벗어나면 액터 삭제
	//if (position.y < 0)
	if (yPosition < 0.0f)
	{
		Destroy();
		return;
	}

}
