#include "PreCompiledHeader/PreCompiledHeader.h"
#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"

GameLevel::GameLevel()
{
	// 커서 감추기
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// 맵 파일 불러와 레벨 로드
		// 파일 읽기
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Stage1.txt", "rb");

	// 파일 처리
	if (file == nullptr)
	{
		std::cout << "맵 파일 열기 실패.\n";
		__debugbreak();
	}

	// 파일 읽기
	// 끝 위치로 이동
	fseek(file, 0, SEEK_END);

	// 이동한 위치의 FP 가져오기
	size_t readSize = ftell(file);

	// FP 원위치
	// fseek(file, 0, SEEK_SET); 아래와 같은 코드
	rewind(file);

	// 파일 읽어서 버퍼에 담기
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
		return;
	}
	buffer[readSize] = '\0';

	// 파일 읽을때 사용할 인덱스
	int index = 0;

	// 좌표 계산을 위한 변수 선언
	int xPosition = 0;
	int yPosition = 0;

	while (index < (int)bytesRead)
	{
		// 한문자씩 읽기
		char mapChar = buffer[index++];

		// 개행 문자인 경우 처리
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		if (mapChar == '1')
		{
			actors.push_back(new Wall(Vector2(xPosition, yPosition)));
		}

		// 맵 문자가 .이면 그라운드 액터 생성
		else if (mapChar == '.')
		{
			actors.push_back(new Ground(Vector2(xPosition, yPosition)));
		}

		// 맵 문자가 b이면 그라운드 액터 생성
		else if (mapChar == 'b')
		{
			actors.push_back(new Box(Vector2(xPosition, yPosition)));
		}

		++xPosition;
	}

	// 버퍼 삭제
	delete[] buffer;

	fclose(file);
}
