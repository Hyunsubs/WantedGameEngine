#pragma once
#include "RTTI.h"
#include "Math/Vector2.h"


// ������ �⺻ ��ü
class ENGINE_API Actor : public RTTI
{
	// RTTI ����
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor();
	virtual ~Actor();

	virtual void Update(float deltaTime);
	virtual void Draw();

	// Setter
	virtual void SetPosition(const Vector2& newPosition);
	


	// Getter
	inline Vector2 Position() const { return position; }


protected:
	// ������ ��ġ
	Vector2 position;

	// ID(Hash) / �̸� �� ���� �������� �˻��� ������ �ϱ� ���� ��� actor���� ������ ID�� ������ ����
	

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;




};

