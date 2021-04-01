#include "CollisionModule.hpp"

#include "TilemapView.hpp"

void CollisionModule::detectTileCollisions(EntityContainer& entities, const TilemapView& tilemapView) const noexcept
{
	for (auto entity : entities)
	{
		const auto collisionTiles = checkTileCollision(entity, tilemapView);
		handleTileCollision(entity, collisionTiles);
	}
}

void CollisionModule::detectEntityCollisions(EntityContainer& entities, const EntityContainer& colliders) const noexcept
{
	for (auto entity : entities)
	{
		for (auto collider : colliders)
		{
			if (entity != collider)
			{
				const auto collisionEntities = checkEntityCollision(entity, collider);
				handleEntityCollision(entity, collisionEntities);
			}
		}
	}
}

CollisionModule::TileList CollisionModule::checkTileCollision(const Entity* entity, const TilemapView& tilemapView) const noexcept
{
	TileList collisionTiles{};

	if (!entity->isDestroyed() && !entity->hasComponent(Entity::ComponentType::Transparency))
	{
		const auto tiles = tilemapView.getTiles(entity->getArea());
		for (auto& tile : tiles)
		{
			if (tile.hasTrait(Tile::TraitType::Collider))
			{
				collisionTiles.push_back(tile);
			}
		}
	}

	return collisionTiles;
}

CollisionModule::EntityList CollisionModule::checkEntityCollision(Entity* entity, const Entity* collider) const noexcept
{
	EntityList collisionEntities{};

	if (!entity->isDestroyed() && !entity->hasComponent(Entity::ComponentType::Transparency))
	{
		if (entity->isIntersects(*collider))
		{
			collisionEntities.push_back(collider);
		}
	}

	return collisionEntities;
}

void CollisionModule::handleTileCollision(Entity* entity, const TileList& collisionTiles) const noexcept
{
	const auto entityArea = entity->getArea();

	for (auto& collisionTile : collisionTiles)
	{
		const auto colliderArea = collisionTile.getArea();
		const auto collisionSide = checkCollisionSide(entityArea, colliderArea);
		if (collisionSide != CollisionSideType::None)
		{
			entity->collision(collisionTile, collisionSide);
			moveEntity(collisionSide, *entity, colliderArea);
		}
	}

	if (collisionTiles.empty())
	{
		entity->falling();
	}
}

void CollisionModule::handleEntityCollision(Entity* entity, const EntityList& collisionEntities) const noexcept
{
	const auto entityArea = entity->getArea();

	for (auto collisionEntity : collisionEntities)
	{
		const auto colliderArea = collisionEntity->getArea();
		const auto collisionSide = checkCollisionSide(entityArea, colliderArea);
		if (collisionSide != CollisionSideType::None)
		{
			if (collisionEntity->hasComponent(Entity::ComponentType::Solid))
			{
				moveEntity(collisionSide, *entity, colliderArea);
			}
			
			entity->collision(*collisionEntity, collisionSide);
		}
	}
}

CollisionSideType CollisionModule::checkCollisionSide(const FloatArea& areaA, const FloatArea& areaB) const noexcept
{
	const auto centerA = areaA.getCenter();
	const auto centerB = areaB.getCenter();

	const auto isTopCollision = centerA.getY() < centerB.getY() &&
								centerA.getY() < areaB.getTop();
	const auto isBottomCollision = centerA.getY() > areaB.getBottom();

	if (isTopCollision)
	{
		return CollisionSideType::Top;
	}
	else if (isBottomCollision)
	{
		return CollisionSideType::Bottom;
	}

	const auto isLeftCollision = centerA.getX() < centerB.getX() &&
								 centerA.getY() > areaB.getTop();
	const auto isRightCollision = centerA.getY() > areaB.getTop() &&
								  centerA.getY() < areaB.getBottom();

	if (isLeftCollision)
	{
		return CollisionSideType::Left;
	}

	if (isRightCollision)
	{
		return CollisionSideType::Right;
	}

	return CollisionSideType::None;
}

void CollisionModule::moveEntity(const CollisionSideType side, Entity& entity, const FloatArea& colliderArea) const noexcept
{
	switch (side)
	{
	case CollisionSideType::Top:
		entity.setPositionY(colliderArea.getTop() - entity.getArea().getHeight());
		break;
	case CollisionSideType::Bottom:
		entity.setPositionY(colliderArea.getBottom() + 1.0f);
		break;
	case CollisionSideType::Left:
		entity.setPositionX(colliderArea.getLeft() - entity.getArea().getWidth());
		break;
	case CollisionSideType::Right:
		entity.setPositionX(colliderArea.getRight() + 1.0f);
		break;
	default:
		break;
	}
}
