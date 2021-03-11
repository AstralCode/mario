#pragma once

#include "CollisionHandler.hpp"

class CreaturesCollisionHandler final : public CollisionHandler
{
public:
	CreaturesCollisionHandler(TilemapView& tilemapView) noexcept;

	void onTileCollision(GameObject* object, const TileIndex& tileIndex) noexcept override;
	void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept override;
};
