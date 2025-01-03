#include "PreCompiledHeader.h"
#include "Engine.h"
#include "../Level/Level.h"

using namespace std;

// 스태틱 변수 초기화
Engine* Engine::instance = nullptr;


Engine::Engine()
	: quit(false)
	, mainLevel(nullptr)
{
	// 싱글톤 객체 설정
	instance = this;
}

Engine::~Engine()
{
	SafeDelete(mainLevel);
}

void Engine::Run()
{
	// 시작 타임 스탬프 저장
	//unsigned long currentTime = timeGetTime();
	//unsigned long previousTime = 0;

	// CPU 시계 사용
	// 고해상도 카운터
	// 메인보드 내에 존재함
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency); // CPU가 초당 낼수 있는 최대 주파수
	
	// 시작 시간 및 이전 시간을 위한 변수
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time); // 프로그램이 실행될때 측정되는 주파수

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	// 프레임 제한
	float targetFrameRate = 144.f;

	// 한 프레임 시간 계산
	float targetOneFrameTime = 1.f / targetFrameRate;


	// Game-Loop
	while (!quit)
	{
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;
		// 프레임 시간 계산
		// 
		// 실행 순간 주파수 - 이전 주파수 = 프로그램 틱이 돌때 소모되는 주파수
		// 프로그램 틱이 돌때 소모되는 주파수 / 전체 주파수(초당 돌수 있는 최대값) = 1프레임당 소모되는 시간
		float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency.QuadPart);
		

		// 지정한 프레임보다 델타 타임이 작으면(실행속도가 빠르면) update draw를 실행하지 않음
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인)
			ProcessInput();

			Update(deltaTime);
			Draw();

			// 키 상태 저장
			SavePreviousKeyStates();

			// 이전 프레임 시간 저장
			previousTime = currentTime;
		}

	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체

	// 메인 레벨 설정 (단일 레벨 기준)
	mainLevel = newLevel;
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
	//  esc 키로 게임 종료
	if (GetKeyDown(VK_ESCAPE))
		QuitGame();

	// 레벨 Update
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}

	cout << "DeltaTime: " << deltaTime << ", " << (1.f / deltaTime) << "\n";
}

void Engine::Draw()
{
	// 레벨 DrawCall
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
