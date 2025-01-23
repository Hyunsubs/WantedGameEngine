#include <iostream>
#include <windows.h>
#include "Engine/Engine.h"
#include "Sound/SoundManager.h"
#include "Sound/SoundObject.h"
#include "Levels/TitleLevel.h"
#include "Levels/OpeningLevel.h"
using namespace std;

int cur_level = 0;

bool print_collision = false;
std::vector<Level*> levels;

int main()
{
	// �� üũ
	CheckMemoryLeak();


	SoundManager::Get().Init();

	// ���� ���� ����
	SetConsoleTitleA("Street Fighter 2 Clone");

	OpeningLevel* opening = new OpeningLevel();
	TitleLevel* level = new TitleLevel();

	// ��� ���� ���� �ʱ�ȭ
	levels.push_back(opening);
	levels.push_back(level);

	for (int i = 0; i < levels.size(); i++)
	{
		levels[i]->Init();
	}

	// ���� ���� ����
	Engine engine;
	engine.LoadLevel(levels[cur_level]);
	engine.Run();

	return 0;
}

