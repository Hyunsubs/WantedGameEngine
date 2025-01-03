#pragma once

class Actor;
class Level
{
public:
	Level();
	virtual ~Level();

	// 액터 추가 함수
	void AddActor(Actor* newActor);

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// 게임 공간에 배치되는 물체(액터) 배열
	Actor** actors;

	// 저장할 수 있는 공간의 크기
	int capacity;

	// 액터의 수
	int count;
};

