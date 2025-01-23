#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"
#include "Util.h"

DrawableActor::DrawableActor(const char* image)
	: Actor()/*, image(image)*/
	, image(image)
{
	this->image.reserve(3000);
}

DrawableActor::DrawableActor(int a, std::string _filepath)
	: Actor()
{
	std::string file = Util::LoadFileContent(_filepath.c_str());
	image = file;
}


DrawableActor::~DrawableActor()
{
}

void DrawableActor::Update(float deltaTime)
{
	width = (int)image.find('\n');
	height = (int)image.size() / width;
}

void DrawableActor::Draw()
{
	Engine::Get().Draw(position, image, color, width, height, reverse);
}


void DrawableActor::SetPosition(const Vector2& newPosition)
{
	// ��ġ�� ���� �ű��.
	Super::SetPosition(newPosition);
}

bool DrawableActor::Intersect(const DrawableActor& other)
{
	// AABB(Axis Aligned Bounding Box).

	// �� x��ǥ �ּ�/�ִ�.
	int min = position.x;
	int max = position.x + width;

	// �ٸ� ������ x��ǥ �ּ�/�ִ�.
	int otherMin = other.position.x;
	int otherMax = other.position.x + other.width;

	// �ٸ� ������ ���� �� ��ġ�� �� ������ �� ��ġ�� ����� �浹 ����.
	if (otherMin > max)
	{
		return false;
	}

	// �ٸ� ������ ������ �� ��ġ�� �� ���� �� ��ġ���� ������ �浹 ����.
	if (otherMax < min)
	{
		return false;
	}

	// ���� �� ��찡 �ƴ϶�� (x��ǥ�� ���� ��ħ), y��ġ ��.
	return position.y == other.position.y;
}

void DrawableActor::OnCollisionEnter(BoundingBox* _target)
{
}

void DrawableActor::OnCollision(BoundingBox* _target)
{
}

void DrawableActor::CollisionEnd(BoundingBox* _target)
{
}
