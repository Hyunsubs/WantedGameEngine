#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(char image)
	: Actor() // 기본 생성자일 경우 명시적으로 할 필요는 없지만 가독성이 좋음
	, image(image)
{
}

void DrawableActor::Draw()
{
	// 부모를 Super라는 키워드로 사용함(UE와 동일한 네이밍)
	Super::Draw(); // Actor의 Draw()


	// 그리기
	// 1단계 : 콘솔 좌표 옮기기
	Engine::Get().SetCursorPosition(position);

	// 2단계 : 그리기 (콘솔 출력)
	Log("%c", image);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	Engine::Get().SetCursorPosition(position);
	Log(" ");

	// 위치를 새로 옮기기
	Super::SetPosition(newPosition);
}
