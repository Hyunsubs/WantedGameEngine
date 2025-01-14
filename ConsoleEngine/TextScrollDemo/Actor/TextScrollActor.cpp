#include "TextScrollActor.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

TextScrollActor::TextScrollActor(const char* message)
{
	// 문자열 길이 구하기
	length = (int)strlen(message);

	// 문자열 복사
	string = new char[length + 1];
	strcpy_s(string, length + 1, message);

	drawText = new char[printWidth + 1];

	// 커서 감추기
	Engine::Get().SetCursorType(CursorType::NoCursor);
}

TextScrollActor::~TextScrollActor()
{
	delete[] string;
	string = nullptr;

	delete[] drawText;
	drawText = nullptr;
}

void TextScrollActor::Update(float deltaTime)
{
	// ESC 종료
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		// Engine::Get().QuitGame();

		Game::Get().ToggleMenu();
	}

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		direction = Direction::Left;
		shouldUpdate = true;
	}

	if (Engine::Get().GetKey(VK_LEFT))
	{
		direction = Direction::Right;
		shouldUpdate = true;
	}

	// 방향키가 안눌렸는지 확인
	if (!Engine::Get().GetKey(VK_LEFT) && !Engine::Get().GetKey(VK_RIGHT))
	{
		shouldUpdate = false;
	}

	if (shouldUpdate)
	{
		if (direction == Direction::Right)
		{
			index = (index + 1) % length;
		}

		else if (direction == Direction::Left)
		{
			index = (index - 1 + length) % length;
		}
	}
}

void TextScrollActor::Draw()
{
	int tempIndex = index;
	
	for (int i = 0; i < printWidth; i++)
	{
		drawText[i] = string[tempIndex];
		tempIndex = (tempIndex + 1) % length;
	}

	drawText[printWidth] = '\0';
	Log(drawText);

	Engine::Get().SetCursorPosition(0, 0);
}
