#pragma once

#include <tuple>

#include "Entity.hpp"

class TilemapView;
class EntityContainer;

class CollisionModule final
{
public:
	void detectCollisions(const EntityContainer& entities, TilemapView& tilemapView) noexcept;

private:
	enum class CollisionSide
	{
		Top,
		Left,
		Right,
		Bottom,
		None
	};

	using TileColliders = std::vector<std::tuple<Entity*, Tile>>;
	using EntityColliders = std::vector<std::tuple<Entity*, Entity*>>;

	void executeTileCollisionHandlers(const TileColliders& colliders) const noexcept;
	void executeEntityCollisionHandlers(const EntityColliders& colliders) const noexcept;

	TileColliders checkTileCollisions(const EntityContainer& entities, TilemapView& tilemapView) const noexcept;
	EntityColliders checkEntityCollisions(const EntityContainer& entities) const noexcept;

	CollisionSide checkCollisionSide(const FloatArea& areaA, const FloatArea& areaB) const noexcept;
};
