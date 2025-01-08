#pragma once
#include "Actor.h"

// <>로 추가하려면 속성창에 추가된 경로만 찾음
// ""가 상대 경로도 찾아서 범위가 넓음

class ENGINE_API DrawableActor : public Actor
{
	RTTI_DECLARATIONS(DrawableActor, Actor)

public:
	DrawableActor(char image = ' ');
	virtual ~DrawableActor() = default;
	
	virtual void Draw() override;
	
	virtual void SetPosition(const Vector2& newPosition) override;



private:
	// 화면에 그릴 문자 값
	char image;

};
