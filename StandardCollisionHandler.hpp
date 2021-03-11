#pragma once

#include "CollisionHandler.hpp"

class StandardCollisionHandler final : public CollisionHandler
{
public:
	StandardCollisionHandler(TilemapView& tilemapView) noexcept;

	void onTileCollision(GameObject* object, const TileIndex& tileIndex) noexcept override;
	void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept override;
};