#pragma once


#include "Actor/DrawableActor.h"


class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	virtual void Update(float deltaTime) override;

public:
	Player(char image = 'P');
	~Player() = default;
};