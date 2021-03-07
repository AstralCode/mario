#pragma once

#include "CollisionHandler.hpp"

class EnemyCollisionHandler final : public CollisionHandler
{
public:
	EnemyCollisionHandler(TilemapView& tilemapView) noexcept;

	void onTileCollision(GameObject* target, const TileIndex& tileIndex) noexcept override;
	void onObjectCollision(GameObject* target, GameObject* object) noexcept override;
};
