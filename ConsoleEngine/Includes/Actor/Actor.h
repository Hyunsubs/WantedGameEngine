#pragma once
#include "RTTI.h"
#include "Math/Vector2.h"


// ������ �⺻ ��ü
class ENGINE_API Actor : public RTTI
{
	// RTTI ����
	RTTI_DECLARATIONS(Actor, RTTI)

	// Level Ŭ������ friend�� ����
	// private�� ������ �����ϵ���
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�
	virtual void Update(float deltaTime);
	virtual void Draw();

	// Setter
	virtual void SetPosition(const Vector2& newPosition);
	
	// Getter
	inline Vector2 Position() const { return position; }

	inline bool IsActive() const { return isActive; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

protected:
	// ������ ��ġ
	Vector2 position;

	// ID(Hash) / �̸� �� ���� �������� �˻��� ������ �ϱ� ���� ��� actor���� ������ ID�� ������ ����
	

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;

};

