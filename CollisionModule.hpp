#pragma once

#include <tuple>

#include "EntityContainer.hpp"

class TilemapView;

class CollisionModule final
{
public:
	using TileList = std::vector<Tile>;
	using EntityList = std::vector<const Entity*>;

	void detectTileCollisions(EntityContainer& entities, const TilemapView& tilemapView) const noexcept;
	void detectEntityCollisions(EntityContainer& entities, const EntityContainer& colliders) const noexcept;

	TileList checkTileCollision(const Entity* entity, const TilemapView& tilemapView) const noexcept;
	EntityList checkEntityCollision(Entity* entity, const Entity* collider) const noexcept;

	void handleTileCollision(Entity* entity, const TileList& collisionTiles) const noexcept;
	void handleEntityCollision(Entity* entity, const EntityList& collisionEntities) const noexcept;

	CollisionSideType checkCollisionSide(const FloatArea& areaA, const FloatArea& areaB) const noexcept;

	void moveEntity(const CollisionSideType side, Entity& entity, const FloatArea& area) const noexcept;
};
