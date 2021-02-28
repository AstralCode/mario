#pragma once

#include <tuple>
#include <vector>
#include <memory>

#include "CollisionHandler.hpp"

class GraphicsItem;
class TilemapView;

class CollisionModule final
{
public:
	CollisionModule(TilemapView& tilemapView) noexcept;

	template <typename TCollisionHandler>
	void addHandler() noexcept;

	void execute(const std::vector<GameObject*> objects) noexcept;

private:
	using TilemapColliders = std::tuple<GameObject*, TileIndex>;
	using ObjectColliders = std::tuple<GameObject*, GameObject*>;

	void executeTilemapCollisionHandlers(const std::vector<TilemapColliders>& colliders) const noexcept;
	void executeObjectCollisionHandlers(const std::vector<ObjectColliders>& colliders) const noexcept;

	std::vector<TilemapColliders> checkTilemapCollisions(const std::vector<GameObject*> objects) const noexcept;
	std::vector<ObjectColliders> checkObjectCollisions(const std::vector<GameObject*> objects) const noexcept;

	std::vector<std::unique_ptr<CollisionHandler>> mCollisionHandlers;

	TilemapView& mTilemapView;
};


template <typename TCollisionHandler>
inline void CollisionModule::addHandler() noexcept
{
	static_assert(std::is_base_of_v<CollisionHandler, TCollisionHandler>, "TCollisionHandler must derived from CollisionHandler");

	mCollisionHandlers.push_back(std::make_unique<TCollisionHandler>(mTilemapView));
}
