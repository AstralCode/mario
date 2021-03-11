#pragma once

#include "CollisionHandler.hpp"

class MarioCollisionHandler final : public CollisionHandler
{
public:
	MarioCollisionHandler(TilemapView& tilemapView) noexcept;

	void onTileCollision(GameObject* object, const TileIndex& tileIndex) noexcept override;
	void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept override;
};
