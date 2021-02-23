#pragma once

#include "SFML/System/Vector2.hpp"

#include "GameObjectIdentifiers.hpp"

class GameObject;
class Tilemap;
class SpritesetContainer;

class CollisionHandler
{
public:
	CollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept;

	virtual ~CollisionHandler() = default;

	virtual void onTileCollision(GameObject* target, const sf::Vector2u& tileIndex) noexcept = 0;
	virtual void onObjectCollision(GameObject* target, GameObject* object) noexcept = 0;

	virtual GameObjectIdentifiers getTarget() const noexcept = 0;

	Tilemap& getTilemap() noexcept;
	SpritesetContainer& getSpritesetContainer() noexcept;

private:
	Tilemap& mTilemap;
	SpritesetContainer& mSpritesetContainer;
};
