#pragma once

#include "Level/Level.h"

class TestLevel : public Level
{
	// RTTI 적용
	RTTI_DECLARATIONS(TestLevel, Level)

public:
	TestLevel();
	~TestLevel();

	virtual void Update(float deltaTime) override;

private:
	int max_mob = 5;
};