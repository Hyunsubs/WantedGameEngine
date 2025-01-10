#include "PreCompiledHeader/PreCompiledHeader.h"
#include "Game/Game.h"
#include "Level/TextScrollLevel.h"
#include <crtdbg.h>

// ȭ�� �����
// List �ڷᱸ���� ���� �Լ� �߰�
// Actor/Level/Engine���� ���� �����ϴ� �Լ� �߰�


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.LoadLevel(new TextScrollLevel());
	game.Run();

	return 0;
}