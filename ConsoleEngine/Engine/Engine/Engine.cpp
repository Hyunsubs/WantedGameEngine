#include "PreCompiledHeader.h"
#include "Engine.h"
#include "../Level/Level.h"
#include "Actor/Actor.h"
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

			// ������Ʈ ������ ���¿����� ������ ������Ʈ ó��
			if (shouldUpdate)
			{
				Update(deltaTime);
				Draw();
			}

			// Ű ���� ����
			SavePreviousKeyStates();

			// ���� ������ �ð� ����
			previousTime = currentTime;

			// ���� ���� (���� ��û�� ���͵� ����)
			if (mainLevel)
			{
				mainLevel->DestroyActor();
			}

			// ������ Ȱ��ȭ
			shouldUpdate = true;
		}

	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// ���� ������ �ִٸ� ���� �� ��ü

	// ���� ���� ���� (���� ���� ����)
	mainLevel = newLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// ���� ó��
	if (mainLevel == nullptr)
		return;

	shouldUpdate = false;
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// ���� ó��
	if (mainLevel == nullptr)
		return;

	shouldUpdate = false;
	targetActor->Destroy();
}

void Engine::SetCursorType(CursorType type)
{
	CONSOLE_CURSOR_INFO info = { };\

	// Ÿ�� ���� �Ӽ� ����ü �� ����
	switch (type)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;
	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;
	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;
	default: 
		break;
	}
	info.bVisible = (int)type;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

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

void Engine::Clear()
{
	// ȭ���� (0,0)���� �̵�
	SetCursorPosition(0, 0);
	
	// ȭ�� �����
	int height = 25;
	for (int i = 0; i < height; i++)
	{
		Log("                              \n");
	}

	// ȭ���� (0,0)���� �̵�
	SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// ȭ�� �����
	Clear();

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
