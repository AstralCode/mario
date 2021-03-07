#pragma once

#include "GameObject.hpp"

class TilemapView;

class CollisionHandler
{
public:
	CollisionHandler(TilemapView& tilemapView) noexcept;
	virtual ~CollisionHandler() = default;

	void setTarget(const GameObjectIdentifiers identifier) noexcept;
	void unsetTarget(const GameObjectIdentifiers identifier) noexcept;

	void setTargets(const GameObjectIdentifierFlags& identifiers) noexcept;
	void unsetTargets(const GameObjectIdentifierFlags& identifiers) noexcept;

	virtual void onTileCollision(GameObject* target, const TileIndex& tileIndex) noexcept = 0;
	virtual void onObjectCollision(GameObject* target, GameObject* object) noexcept = 0;

	const GameObjectIdentifierFlags& getTargets() const noexcept;

	bool isSetTarget(const GameObjectIdentifiers identifier) const noexcept;

protected:
	TilemapView& mTilemapView;

private:
	GameObjectIdentifierFlags mTargets;
};
