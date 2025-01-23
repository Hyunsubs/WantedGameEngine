#pragma once

#include <Actor/AnimatedActor.h>


class ENGINE_API BoundingBox : public AnimatedActor
{
	RTTI_DECLARATIONS(BoundingBox, AnimatedActor)
public:
	BoundingBox();
	~BoundingBox();


	void SetSize(int _width, int _height);
	inline int Height() { return height; }
	inline int Width() { return width; }

	inline void SetOwner(DrawableActor* _target) { owner = _target; }
	inline void SetOffset(int _x, int _y) { offset.x = _x; offset.y = _y; }

	inline void SetLayerType(LAYER _type) { layerType = _type; }
	inline LAYER GetLayerType() { return layerType; }

	// Collision
	virtual void OnCollisionEnter(BoundingBox* _target) override;
	virtual void OnCollision(BoundingBox* _target) override;
	virtual void CollisionEnd(BoundingBox* _target) override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	inline Actor* GetOwner() { return owner; }

protected:
	int width = 0;
	int height = 0;

	bool collided = false;

	Vector2 offset = {};

	int x_min = 0;
	int y_min = 0;
	int x_max = 0;
	int y_max = 0;

	LAYER layerType = LAYER::NONE;

	std::string image_buffer = "";

	Actor* owner = nullptr;

	friend class CollisionManager;
};