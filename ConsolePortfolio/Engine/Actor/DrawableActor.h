#pragma once

#pragma warning (disable : 4251)

#include "Actor.h"
#include <string>

class ENGINE_API DrawableActor : public Actor
{
	// RTTI.
	RTTI_DECLARATIONS(DrawableActor, Actor)

public:
	DrawableActor(const char* image = "");
	DrawableActor(int a, std::string _filepath);
	//virtual ~DrawableActor() = default;
	virtual ~DrawableActor();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPosition) override;

	// �浹 Ȯ�� �Լ�.
	bool Intersect(const DrawableActor& other);

	// Getter.
	inline int Width() const { return width; }
	inline int Height() const { return height; }


	// Collision
	virtual void OnCollisionEnter(BoundingBox* _target) override;
	virtual void OnCollision(BoundingBox* _target) override;
	virtual void CollisionEnd(BoundingBox* _target) override;

protected:

	// ȭ�鿡 �׸� ���� ��.
	std::string image;

	// �ʺ�(ó�� \n�� ������ ������ ����).
	int width = 0;
	// ����(��ü ���� / �ʺ�)
	int height = 0;

	bool fixed = false;


	// ���� ��.
	Color color = Color::White;
};