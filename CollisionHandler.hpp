#pragma once

#include "GameObject.hpp"

class CollisionHandler
{
public:
	virtual ~CollisionHandler() = default;

	void setTarget(const GameObjectIdentifiers identifier) noexcept;
	void unsetTarget(const GameObjectIdentifiers identifier) noexcept;

	void setTargets(const GameObjectIdentifierFlags& identifiers) noexcept;
	void unsetTargets(const GameObjectIdentifierFlags& identifiers) noexcept;

	virtual void onTileCollision(GameObject* target, const Tile& tile) noexcept = 0;
	virtual void onObjectCollision(GameObject* objectA, GameObject* objectB) noexcept = 0;

	const GameObjectIdentifierFlags& getTargets() const noexcept;

	bool isSetTarget(const GameObjectIdentifiers identifier) const noexcept;

private:
	GameObjectIdentifierFlags mTargets;
};
