#pragma once

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

	using Tiles = std::vector<Tile>;;
	using Entities = std::vector<const Entity*>;

	using TileColliders = std::vector< std::pair<Entity*, Tiles>>;
	using EntityColliders = std::vector<std::pair<Entity*, Entities>>;

	void handleTileCollisions(const TileColliders& colliders) const noexcept;
	void handleEntityCollisions(const EntityColliders& colliders) const noexcept;

	TileColliders checkTileCollisions(const EntityContainer& entities, TilemapView& tilemapView) const noexcept;
	EntityColliders checkEntityCollisions(const EntityContainer& entities) const noexcept;

	CollisionSide checkCollisionSide(const FloatArea& areaA, const FloatArea& areaB) const noexcept;

	void filterColliderTiles(Tiles& tiles) const noexcept;

	bool isEntityMove(Entity* entity) const noexcept;
};
