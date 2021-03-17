#pragma once

#include "CollisionHandler.hpp"

class StandardCollisionHandler final : public CollisionHandler
{
public:
	StandardCollisionHandler() noexcept;

	void onTileCollision(GameObject* object, const Tile& tile) noexcept override;
	void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept override;
};