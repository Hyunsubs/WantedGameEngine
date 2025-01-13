#include "PreCompiledHeader/PreCompiledHeader.h"
#include "Game/Game.h"
#include "Level/TextScrollLevel.h"
#include <crtdbg.h>

// 화면 지우기
// List 자료구조에 삭제 함수 추가
// Actor/Level/Engine에서 액터 제거하는 함수 추가


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.LoadLevel(new TextScrollLevel());
	game.Run();

	return 0;
}