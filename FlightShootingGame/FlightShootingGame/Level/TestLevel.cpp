#include "PreCompiledHeader/PreCompiledHeader.h"
#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/EnemyBullet.h"
#include <windows.h>

// 적 캐릭터 종류.
static const char* enemyType[]
{
	";(^);",
	"zZTZz",
	"oO&Oo",
	"<=-=>",
	")~O~(",
	"[[0]]"
};


int TestLevel::score = 0;

TestLevel::TestLevel()
{
	Player* player = new Player("jet");
	AddActor(player);
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 예외처리
	if (deltaTime > 1.f)
	{
		return;
	}

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	// 점수 출력
	SetCmdColor(Color::Green);
	Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y + 1);
	Log("Score: %d", score);
	SetCmdColor(Color::White);

	SpawnEnemy(deltaTime);

	// 플레이어 탄약과 적의 충돌 처리
	ProcessCollisionPlayerBulletAndEnemy();
	ProcessCollisionPlayerAndEnemyBullet();
}

void TestLevel::GameOverAnimation(Player* player)
{
	Vector2 playerPos = player->Position();
	SetCmdColor(Color::Red);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		COORD(playerPos.x, playerPos.y));
	Log("\n");
	Log("G");
	Sleep(200);
	Log("A");
	Sleep(200);
	Log("M");
	Sleep(200);
	Log("E");
	Sleep(200);
	Log("O");
	Sleep(200);
	Log("V");
	Sleep(200);
	Log("E");
	Sleep(200);
	Log("R");
	Sleep(200);
	Log(".");
	Sleep(200);
	SetCmdColor(Color::White);
	Log("\n");
}

void TestLevel::SpawnEnemy(float deltaTime)
{
	// 적생성
	static float elapsedTime = 0.f;
	static float spawnTime = RandomPercent(1.f, 3.f);

	// 타이머
	elapsedTime += deltaTime;
	if (elapsedTime < spawnTime)
	{
		return;
	}

	// 타이머 리셋
	elapsedTime = 0.f;
	spawnTime = RandomPercent(1.f, 3.f);

	// 적생성
	static int length = sizeof(enemyType) / sizeof(enemyType[0]);
	int index = Random(0, length - 1);
	Enemy* pEnemy = new Enemy(enemyType[index], Random(5, 15));
	AddActor(pEnemy);
}

void TestLevel::ProcessCollisionPlayerBulletAndEnemy()
{
	// 탄약 및 적 캐릭터의 배열 선언
	std::vector<PlayerBullet*> bullets;
	std::vector<Enemy*> enemies;

	// 레벨에 배치된 액터를 순환하면서 리스트 채우기
	for (Actor* actor : actors)
	{
		// 탄약으로 형변환 후 확인해서 리스트 채우기
		PlayerBullet* bullet = actor->As<PlayerBullet>();
		if (bullet)
		{
			bullets.emplace_back(bullet);
			continue;
		}

		// 적으로 형변환 후 확인해서 리스트 채우기
		Enemy* enemy = actor->As<Enemy>();
		if (enemy)
		{
			enemies.emplace_back(enemy);
		}
	}
	
	// 예외 처리
	if (bullets.size() == 0 || enemies.size() == 0)
		return;

	for (PlayerBullet* bullet : bullets)
	{
		for (Enemy* enemy : enemies)
		{
			// 적이 비활성화 상태라면 건너뛰기
			if (!enemy->IsActive())
			{
				continue;
			}

			// 충돌 처리
			if (enemy->Intersect(*bullet))
			{
				// 충돌했으면 적 제거
				enemy->Destroy();

				// 탄약도 제거
				bullet->Destroy();

				// 점수 추가
				score += 1000;
			}
		}
	}
}

void TestLevel::ProcessCollisionPlayerAndEnemyBullet()
{
	// 플레이어와 적 탄약 변수 선언.
	Player* player = nullptr;
	List<EnemyBullet*> bullets;

	// 레벨에 배치된 액터를 순회하면서 리스트 채우기.
	for (Actor* actor : actors)
	{
		// 플레이어 검색.
		if (!player)
		{
			player = actor->As<Player>();
			continue;
		}

		// 탄약으로 형변환 후 확인해서 리스트 채우기.
		EnemyBullet* bullet = actor->As<EnemyBullet>();
		if (bullet)
		{
			bullets.PushBack(bullet);
			continue;
		}
	}

	// 예외처리.
	if (player == nullptr || bullets.Size() == 0)
	{
		return;
	}

	// 배열 순회하면서 충돌 처리.
	for (EnemyBullet* bullet : bullets)
	{
		// 탄약과 플레이어가 충돌했는지 확인.
		if (player->Intersect(*bullet))
		{
			GameOverAnimation(player);
			player->Destroy();
			

			// 게임 종료.
			system("cls");
			Engine::Get().QuitGame();
		}
	}
}
