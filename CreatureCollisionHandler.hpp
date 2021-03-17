#pragma once

#include "CollisionHandler.hpp"

class CreatureCollisionHandler final : public CollisionHandler
{
public:
	CreatureCollisionHandler() noexcept;

	void onTileCollision(GameObject* object, const Tile& tile) noexcept override;
	void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept override;
};
