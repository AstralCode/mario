#pragma once

#include "CollisionHandler.hpp"

class MarioCollisionHandler final : public CollisionHandler
{
public:
	MarioCollisionHandler(GraphicsScene& scene) noexcept;

	void onTileCollision(GameObject* target, const TileIndex& tileIndex) noexcept override;
	void onObjectCollision(GameObject* target, GameObject* object) noexcept override;
};
