#include "PreCompiledHeader/PreCompiledHeader.h"
#include "Game/Game.h"
#include "Level/TestLevel.h"

// 화면 지우기
// List 자료구조에 삭제 함수 추가
// Actor/Level/Engine에서 액터 제거하는 함수 추가

int main()
{
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new TestLevel);
	game.Run();

	// cv::imread("asd.jpg");

	return 0;
}