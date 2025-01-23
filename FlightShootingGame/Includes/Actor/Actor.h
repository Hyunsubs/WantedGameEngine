#pragma once
#include "RTTI.h"
#include "Math/Vector2.h"


// 레벨의 기본 물체
class ENGINE_API Actor : public RTTI
{
	// RTTI 선언
	RTTI_DECLARATIONS(Actor, RTTI)

	// Level 클래스를 friend로 선언
	// private에 접근이 가능하도록
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// 루프 처리 함수
	virtual void Update(float deltaTime);
	virtual void Draw();

	// Setter
	virtual void SetPosition(const Vector2& newPosition);
	
	// Getter
	inline Vector2 Position() const { return position; }

	inline bool IsActive() const { return isActive && !isExpired; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

protected:
	// 액터의 위치
	Vector2 position;

	// ID(Hash) / 이름 값 보통 엔진에선 검색을 빠르게 하기 위해 모든 actor들이 고유한 ID를 가지고 있음
	

	// 활성화 상태인지를 나타내는 변수
	bool isActive;

	// 액터의 제거 요청이 됐는지 여부를 나타내는 변수
	bool isExpired;

};

