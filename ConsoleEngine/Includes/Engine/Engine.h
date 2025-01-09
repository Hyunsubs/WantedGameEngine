#pragma once
#include "Math/Vector2.h"

// �Է� ó���� ���� ����ü
struct KeyState
{
	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool isKeyDown = false;
	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool wasKeyDown = false;
};

// Ŀ���� ������ ������ �� ����� ������
enum class CursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor,
	End,
};



class Level;
class Actor;
// ���� Ŭ����
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void LoadLevel(Level* newLevel);
	
	// ���� �߰� ���� �Լ�
	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targetActor);

	// ȭ�� ��ǥ ���� �Լ�.
	void SetCursorType(CursorType type);
	void SetCursorPosition(const Vector2& position);
	void SetCursorPosition(int x, int y);


	// Ÿ�� ������ �ӵ� ����
	inline void SetTargetFrameRate(float targetFrameRate)
	{
		this->targetFrameRate = targetFrameRate;
		targetOneFrameTime = 1.f / targetFrameRate;
	}

	// �Է� ���� �Լ�
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);


	// ���� ���� �Լ�
	void QuitGame();

	// �̱��� ��ü ���� �Լ�
	static Engine& Get();

protected:
	void ProcessInput();			// �Է� ó��
	void Update(float deltaTime);	// Tick();

	void Clear();					// ȭ�� �����
	void Draw();					// Render();

	// ���� �������� Ű ���¸� �����ϴ� �Լ�
	void SavePreviousKeyStates();

private:
	// Ÿ�� ������ ���� (�ʴ� ������)
	float targetFrameRate = 60.f;

	// �� ������ �ð� �� (���� : ��)
	float targetOneFrameTime = 0.f;

	// ������ �� ������ ����
	bool quit;

	// Ű ���¸� �����ϴ� �迭
	KeyState keyState[256];

	// �̱��� ������ ���� ���� ���� ����
	static Engine* instance;

	// ���� ���� ����
	Level* mainLevel;

	// �������� ������Ʈ �ؾ� �ϴ��� ���θ� ��Ÿ���� ����
	bool shouldUpdate = true;
};
