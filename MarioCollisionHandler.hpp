#pragma once

#include "CollisionHandler.hpp"

class MarioCollisionHandler final : public CollisionHandler
{
public:
	MarioCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept;

	void onTileCollision(GameObject* target, const unsigned int tileIdentifier) noexcept override;
	void onObjectCollision(GameObject* target, GameObject* object) noexcept override;

	GameObjectIdentifiers getTarget() const noexcept override;
};
