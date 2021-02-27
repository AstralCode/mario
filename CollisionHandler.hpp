#pragma once

#include "SFML/System/Vector2.hpp"

#include "Tilemap.hpp"
#include "GameObject.hpp"

class CollisionHandler
{
public:
	CollisionHandler(Tilemap& tilemap) noexcept;
	virtual ~CollisionHandler() = default;

	void setTarget(const GameObjectIdentifiers identifier) noexcept;
	void unsetTarget(const GameObjectIdentifiers identifier) noexcept;

	void setTargets(const GameObjectIdentifierFlags& identifiers) noexcept;
	void unsetTargets(const GameObjectIdentifierFlags& identifiers) noexcept;

	virtual void onTileCollision(GameObject* target, const TileIndex& tileIndex) noexcept = 0;
	virtual void onObjectCollision(GameObject* target, GameObject* object) noexcept = 0;

	const GameObjectIdentifierFlags& getTargets() const noexcept;

	Tilemap& getTilemap() noexcept;

	bool isSetTarget(const GameObjectIdentifiers identifier) const noexcept;

private:
	Tilemap& mTilemap;

	GameObjectIdentifierFlags mTargets;
};
