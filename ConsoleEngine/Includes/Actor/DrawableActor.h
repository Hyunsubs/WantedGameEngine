#pragma once
#include "Actor.h"

// <>�� �߰��Ϸ��� �Ӽ�â�� �߰��� ��θ� ã��
// ""�� ��� ��ε� ã�Ƽ� ������ ����

class ENGINE_API DrawableActor : public Actor
{
	RTTI_DECLARATIONS(DrawableActor, Actor)

public:
	DrawableActor(char image = ' ');
	virtual ~DrawableActor() = default;
	
	virtual void Draw() override;
	
	virtual void SetPosition(const Vector2& newPosition) override;



private:
	// ȭ�鿡 �׸� ���� ��
	char image;

};
