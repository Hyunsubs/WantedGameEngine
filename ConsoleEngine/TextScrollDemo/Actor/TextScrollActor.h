#pragma once
#include "Actor/Actor.h"


class TextScrollActor : public Actor
{
	// 입력 방향 열거형 선언
	enum class Direction
	{
		None = -1,
		Left = 0,
		Right = 1,
	};


	RTTI_DECLARATIONS(TextScrollActor, Actor)

public:
	TextScrollActor(const char* message);
	~TextScrollActor();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	// 방향 변수
	Direction direction = Direction::None;

	// 업데이트 여부를 나타내는 변수
	bool shouldUpdate = false;

	// 화면에 보여줄 문자열 값
	char* string = nullptr;

	// 문자열 길이
	int length = 0;

	// 화면에 보여줄 문자열의 시작 인덱스
	int index = 0;

	// 화면에 보여줄 문자 길이
	int printWidth = 20;
	
	char* drawText = nullptr;
};