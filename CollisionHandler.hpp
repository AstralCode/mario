#pragma once

#include "GameObjectIdentifiers.hpp"

class GameObject;
class Tilemap;
class SpritesetContainer;

class CollisionHandler
{
public:
	CollisionHandler(Tilemap& tilemap, SpritesetContainer& spritesetContainer) noexcept;

	virtual ~CollisionHandler() = default;

	virtual void onCollision(GameObject* target, GameObject* object) noexcept = 0;

	virtual GameObjectIdentifiers getTarget() const noexcept = 0;

	Tilemap& getTilemap() noexcept;
	SpritesetContainer& getSpritesetContainer() noexcept;

private:
	Tilemap& mTilemap;
	SpritesetContainer& mSpritesetContainer;
};
