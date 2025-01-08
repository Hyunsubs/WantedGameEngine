#include "PreCompiledHeader.h"
#include "Engine.h"
#include "../Level/Level.h"
using namespace std;

// ����ƽ ���� �ʱ�ȭ
Engine* Engine::instance = nullptr;


Engine::Engine()
	: quit(false)
	, mainLevel(nullptr)
{
	// �̱��� ��ü ����
	instance = this;

	// �⺻ Ÿ�� ������ �ӵ� ����
	SetTargetFrameRate(60.f);

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0; // Ŀ���� ������ ���� ����(0�̸� �Ⱥ���, 0���� ���� ���̸� ����)
	cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

Engine::~Engine()
{
	SafeDelete(mainLevel);
}

void Engine::Run()
{
	// ���� Ÿ�� ������ ����
	//unsigned long currentTime = timeGetTime();
	//unsigned long previousTime = 0;

	// CPU �ð� ���
	// ���ػ� ī����
	// ���κ��� ���� ������
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency); // CPU�� �ʴ� ���� �ִ� �ִ� ���ļ�
	
	// ���� �ð� �� ���� �ð��� ���� ����
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time); // ���α׷��� ����ɶ� �����Ǵ� ���ļ�

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	// Game-Loop
	while (!quit)
	{
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;
		// ������ �ð� ���
		// 
		// ���� ���� ���ļ� - ���� ���ļ� = ���α׷� ƽ�� ���� �Ҹ�Ǵ� ���ļ�
		// ���α׷� ƽ�� ���� �Ҹ�Ǵ� ���ļ� / ��ü ���ļ�(�ʴ� ���� �ִ� �ִ밪) = 1�����Ӵ� �Ҹ�Ǵ� �ð�
		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);
		
		// ������ Ȯ��
		// ������ �����Ӻ��� ��Ÿ Ÿ���� ������(����ӵ��� ������) update draw�� �������� ����
		if (deltaTime >= targetOneFrameTime)
		{
			// �Է� ó�� (���� Ű�� ���� ���� Ȯ��)
			ProcessInput();

			Update(deltaTime);
			Draw();

			// Ű ���� ����
			SavePreviousKeyStates();

			// ���� ������ �ð� ����
			previousTime = currentTime;
		}

	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// ���� ������ �ִٸ� ���� �� ��ü

	// ���� ���� ���� (���� ���� ����)
	mainLevel = newLevel;
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.x, position.y);
}

void Engine::SetCursorPosition(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
	return false;
}

void Engine::QuitGame()
{
	quit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::ProcessInput()
{
	for (int i = 0; i < 256; i++)
	{
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	// ���� Update
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}
}

void Engine::Draw()
{
	// ���� DrawCall
	if (mainLevel != nullptr)
	{
		mainLevel->Draw();
	}
}

void Engine::SavePreviousKeyStates()
{
	for (int i = 0; i < 256; i++)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}
