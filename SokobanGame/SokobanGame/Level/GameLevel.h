#pragma once
#include <Level/Level.h>

// 소코반 게임 레벨
class DrawableActor;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

private:
	// 벽/땅 액터 배열
	std::vector<DrawableActor*> map;
};
