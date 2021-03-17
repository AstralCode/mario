#pragma once

#include "CollisionHandler.hpp"

class MarioCollisionHandler final : public CollisionHandler
{
public:
	MarioCollisionHandler() noexcept;

	void onTileCollision(GameObject* object, const Tile& tile) noexcept override;
	void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept override;
};
