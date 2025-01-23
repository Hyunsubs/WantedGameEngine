#pragma once

#include <Actor/DrawableActor.h>

// 플레이어가 걸어다닐 수 있는 바닥(땅) 액터.
class Box : public DrawableActor
{
	RTTI_DECLARATIONS(Box, DrawableActor)

public:
	Box(const Vector2& position);

private:
	Color color;
};

