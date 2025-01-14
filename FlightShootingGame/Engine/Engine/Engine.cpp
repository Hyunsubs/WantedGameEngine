#include "PreCompiledHeader.h"
#include "Engine.h"
#include "../Level/Level.h"
#include "Actor/Actor.h"
#include <time.h>
using namespace std;

// 스태틱 변수 초기화
Engine* Engine::instance = nullptr;

#define CONSOLE_WIDTH 40
#define CONSOLE_HEIGHT 25

Engine::Engine()
	: quit(false)
	, mainLevel(nullptr)
	, screenSize(CONSOLE_WIDTH, CONSOLE_HEIGHT)
{
	// 랜덤 시드 설정
	srand(static_cast<unsigned int>(time(nullptr)));

	// 싱글톤 객체 설정
	instance = this;

	// 기본 타겟 프레임 속도 설정
	SetTargetFrameRate(60.f);

	// 화면 지울 때 사용할 버퍼 초기화.
	// 1. 버퍼 크기 할당.
	emptyStringBuffer = new char[(screenSize.x + 1) * screenSize.y + 1];

	// 버퍼 덮어쓰기
	memset(emptyStringBuffer, ' ', (screenSize.x + 1) * screenSize.y + 1);


	// 2. 값 할당.
	for (int y = 0; y < screenSize.y; ++y)
	{
		// 각 줄 끝에 개행 문자 추가.
		emptyStringBuffer[(y * (screenSize.x + 1)) + screenSize.x] = '\n';
	}

	// 마지막에 널 문자 추가.
	emptyStringBuffer[(screenSize.x + 1) * screenSize.y] = '\0';


}

Engine::~Engine()
{
	SafeDelete(mainLevel);
	delete[] emptyStringBuffer;
	emptyStringBuffer = nullptr;
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
	int64_t previousTime = currentTime;

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
		
		// 프레임 확인
		// 지정한 프레임보다 델타 타임이 작으면(실행속도가 빠르면) update draw를 실행하지 않음
		if (deltaTime >= targetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인)
			ProcessInput();

			// 업데이트 가능한 상태에서만 프레임 업데이트 처리
			if (shouldUpdate)
			{
				Update(deltaTime);
				Draw();
			}

			// 키 상태 저장
			SavePreviousKeyStates();

			// 이전 프레임 시간 저장
			previousTime = currentTime;

			// 액터 정리 (삭제 요청된 액터들 정리)
			if (mainLevel)
			{
				//mainLevel->DestroyActor();
				mainLevel->ProcessAddedAndDestroyedActor();
			}

			// 프레임 활성화
			shouldUpdate = true;
		}

	}
}

void Engine::LoadLevel(Level* newLevel)
{
	// 기존 레벨이 있다면 삭제 후 교체

	// 메인 레벨 설정 (단일 레벨 기준)
	mainLevel = newLevel;
}

void Engine::AddActor(Actor* newActor)
{
	// 예외 처리
	if (mainLevel == nullptr)
		return;

	shouldUpdate = false;
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	// 예외 처리
	if (mainLevel == nullptr)
		return;

	shouldUpdate = false;
	targetActor->Destroy();
}

void Engine::SetCursorType(CursorType type)
{
	CONSOLE_CURSOR_INFO info = { };\

	// 타입 별로 속성 구조체 값 설정
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
	// 레벨 Update
	if (mainLevel != nullptr)
	{
		mainLevel->Update(deltaTime);
	}
}

void Engine::Clear()
{
	// 화면의 (0,0)으로 이동
	SetCursorPosition(0, 0);
	
	cout << emptyStringBuffer;

	// 화면의 (0,0)으로 이동
	SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	// 화면 지우기
	Clear();

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
