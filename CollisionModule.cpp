#include "CollisionModule.hpp"

#include "EntityContainer.hpp"
#include "TilemapView.hpp"

void CollisionModule::detectCollisions(const EntityContainer& entities, TilemapView& tilemapView) noexcept
{
	const auto tileColliders = checkTileCollisions(entities, tilemapView);
	const auto entityColliders = checkEntityCollisions(entities);

	handleTileCollisions(tileColliders);
	handleEntityCollisions(entityColliders);
}

void CollisionModule::handleTileCollisions(const TileColliders& colliders) const noexcept
{
	for (auto& [entity, collisionTiles] : colliders)
	{
		const auto entityArea = entity->getArea();

		for (auto& collisionTile : collisionTiles)
		{
			const auto collisionSide = checkCollisionSide(entityArea, collisionTile.area);
			if (collisionSide != CollisionSideType::None)
			{
				entity->tileCollision(collisionTile, collisionSide);
				moveEntity(collisionSide, *entity, collisionTile.area);
			}
		}
	}
}

void CollisionModule::handleEntityCollisions(const EntityColliders& colliders) const noexcept
{
	for (auto& [entity, collisionEntities] : colliders)
	{
		const auto entityArea = entity->getArea();

		for (auto collisionEntity : collisionEntities)
		{
			const auto colliderArea = collisionEntity->getArea();

			const auto collisionSide = checkCollisionSide(entityArea, colliderArea);
			if (collisionSide != CollisionSideType::None)
			{
				entity->entityCollision(*collisionEntity, collisionSide);
			}
		}
	}
}

CollisionModule::TileColliders CollisionModule::checkTileCollisions(const EntityContainer& entities, TilemapView& tilemapView) const noexcept
{
	TileColliders colliders{};
	
	for (auto entity : entities)
	{
		Tiles collisionTiles = tilemapView.getTiles(entity->getArea());
		filterColliderTiles(collisionTiles);

		if (!collisionTiles.empty())
		{
			colliders.emplace_back(entity, std::move(collisionTiles));
		}
		else
		{
			entity->falling();
		}
	}

	return colliders;
}

CollisionModule::EntityColliders CollisionModule::checkEntityCollisions(const EntityContainer& entities) const noexcept
{
	EntityColliders colliders{};

	for (auto entitiesIterator = entities.cbegin(); entitiesIterator != entities.cend(); entitiesIterator++)
	{
		Entities collisionEntities{};

		Entity* const entity = *entitiesIterator;

		for (auto collisionEntitiesIterator = entities.cbegin(); collisionEntitiesIterator != entities.cend(); collisionEntitiesIterator++)
		{
			if (entitiesIterator != collisionEntitiesIterator)
			{
				Entity* const collisionEntity = *collisionEntitiesIterator;

				if (entity->isIntersectsItem(*collisionEntity))
				{
					collisionEntities.push_back(collisionEntity);
				}
			}
		}

		if (!collisionEntities.empty())
		{
			colliders.emplace_back(entity, std::move(collisionEntities));
		}
	}

	return colliders;
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
	else if(isBottomCollision)
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

void CollisionModule::filterColliderTiles(Tiles& tiles) const noexcept
{
	auto tilesIt = std::remove_if(tiles.begin(), tiles.end(), [](auto& tile)
	{
		return !tile.attributes.isSet(Tile::Attributes::Collider);
	});

	tiles.erase(tilesIt, tiles.cend());
}

bool CollisionModule::isEntityMove(Entity* entity) const noexcept
{
	return entity->getAcceleration().getX() || entity->getAcceleration().getY();
}
