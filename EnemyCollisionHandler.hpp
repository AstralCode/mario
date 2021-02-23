#pragma once

#include "CollisionHandler.hpp"

class EnemyCollisionHandler final : public CollisionHandler
{
public:
	EnemyCollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept;

	void onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept override;
	void onObjectCollision(GameObject* target, GameObject* object) noexcept override;
};
