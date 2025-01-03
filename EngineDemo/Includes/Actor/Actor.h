#pragma once
#include "PreCompiledHeader.h"

// 레벨의 기본 물체
class ENGINE_API Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ID(Hash) / 이름 값 보통 엔진에선 검색을 빠르게 하기 위해 모든 actor들이 고유한 ID를 가지고 있음
	

	// 활성화 상태인지를 나타내는 변수
	bool isActive;

	// 액터의 제거 요청이 됐는지 여부를 나타내는 변수
	bool isExpired;




};

