#pragma once
#include "PreCompiledHeader.h"

// ������ �⺻ ��ü
class ENGINE_API Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	// ID(Hash) / �̸� �� ���� �������� �˻��� ������ �ϱ� ���� ��� actor���� ������ ID�� ������ ����
	

	// Ȱ��ȭ ���������� ��Ÿ���� ����
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired;




};

