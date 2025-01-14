#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(const char* image)
	: Actor()
{
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);
	
	// 너비 설정
	width = static_cast<int>(length - 1);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();


	Engine::Get().SetCursorPosition(position);

	
	Log(image);
}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	Super::SetPosition(newPosition);
}