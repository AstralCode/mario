#pragma once

#include <tuple>

#include "CollisionHandler.hpp"

class TilemapView;
class GameObjectContainer;

class CollisionModule final
{
public:
	CollisionModule(TilemapView& tilemapView) noexcept;

	template <typename TCollisionHandler>
	void addHandler() noexcept;

	void detectCollisions(const GameObjectContainer& objects) noexcept;

private:
	using TileColliders = std::vector<std::tuple<GameObject*, Tile>>;
	using ObjectColliders = std::vector<std::tuple<GameObject*, GameObject*>>;

	void executeTileCollisionHandlers(const TileColliders& colliders) const noexcept;
	void executeObjectCollisionHandlers(const ObjectColliders& colliders) const noexcept;

	TileColliders checkTileCollisions(const GameObjectContainer& objects) const noexcept;
	ObjectColliders checkObjectCollisions(const GameObjectContainer& objects) const noexcept;

	std::vector<std::unique_ptr<CollisionHandler>> mCollisionHandlers;

	TilemapView& mTilemapView;
};

template <typename TCollisionHandler>
inline void CollisionModule::addHandler() noexcept
{
	static_assert(std::is_base_of_v<CollisionHandler, TCollisionHandler>, "TCollisionHandler must derived from CollisionHandler");

	mCollisionHandlers.push_back(std::make_unique<TCollisionHandler>());
}
