#pragma once
#include "Container/List.h"
#include "RTTI.h"

class Actor;
class ENGINE_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	virtual ~Level();

	// 액터 추가 함수
	void AddActor(Actor* newActor);
	
	// 삭제 요청이 된 액터를 정리하는 함수
	//void DestroyActor();
	void ProcessAddedAndDestroyedActor();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// 게임 공간에 배치되는 물체(액터) 배열
	std::vector<Actor*> actors;

	// 추가 요청된 액터
	Actor* addRequestedActor = nullptr;
};

