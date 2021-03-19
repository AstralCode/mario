#pragma once

#include <tuple>

#include "GameObject.hpp"

class TilemapView;
class GameObjectContainer;

class CollisionModule final
{
public:
	enum class Side
	{
		Top,
		Left,
		Right,
		Bottom,
		None
	};

	void detectCollisions(const GameObjectContainer& objects, TilemapView& tilemapView) noexcept;

private:
	using TileColliders = std::vector<std::tuple<GameObject*, Tile>>;
	using ObjectColliders = std::vector<std::tuple<GameObject*, GameObject*>>;

	void executeTileCollisionHandlers(const TileColliders& colliders) const noexcept;
	void executeObjectCollisionHandlers(const ObjectColliders& colliders) const noexcept;

	TileColliders checkTileCollisions(const GameObjectContainer& objects, TilemapView& tilemapView) const noexcept;
	ObjectColliders checkObjectCollisions(const GameObjectContainer& objects) const noexcept;

	Side checkCollisionSide(const FloatArea& areaA, const FloatArea& areaB) const noexcept;
};
