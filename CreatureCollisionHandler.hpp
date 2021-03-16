#pragma once

#include "CollisionHandler.hpp"

class CreatureCollisionHandler final : public CollisionHandler
{
public:
	CreatureCollisionHandler(TilemapView& tilemapView) noexcept;

	void onTileCollision(GameObject* object, const TileIndex& tileIndex) noexcept override;
	void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept override;
};
