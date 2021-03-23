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
		auto entityPosition = entity->getPosition();

		for (auto& collisionTile : collisionTiles)
		{
			const auto collisionSide = checkCollisionSide(entityArea, collisionTile.area);
			switch (collisionSide)
			{
				case CollisionSide::Top:
					entityPosition.setY(collisionTile.area.getTop() - entityArea.getHeight());
					entity->tileCollision(collisionTile, Sides::Top);
					break;
				case CollisionSide::Bottom:
					entityPosition.setY(collisionTile.area.getBottom() - 1.0f);
					entity->tileCollision(collisionTile, Sides::Bottom);
					break;
				case CollisionSide::Left:
					entityPosition.setX(collisionTile.area.getLeft() - entityArea.getWidth());
					entity->tileCollision(collisionTile, Sides::Left);
					break;
				case CollisionSide::Right:
					entityPosition.setX(collisionTile.area.getRight() + 1.0f);
					entity->tileCollision(collisionTile, Sides::Right);
					break;
				default:
					break;
			}

			if (collisionSide != CollisionSide::None)
			{
				entity->setPosition(entityPosition);
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
			const auto collisionEntityArea = collisionEntity->getArea();
			const auto collisionSide = checkCollisionSide(entityArea, collisionEntityArea);
			switch (collisionSide)
			{
				case CollisionSide::Top:
					entity->setPositionY(collisionEntityArea.getTop() - entityArea.getHeight());
					entity->entityCollision(*collisionEntity, Sides::Top);
					break;
				case CollisionSide::Bottom:
					entity->setPositionY(collisionEntityArea.getBottom() + 1.0f);
					entity->entityCollision(*collisionEntity, Sides::Bottom);
					break;
				case CollisionSide::Left:
					entity->setPositionX(collisionEntityArea.getLeft() - entityArea.getWidth());
					entity->entityCollision(*collisionEntity, Sides::Left);
					break;
				case CollisionSide::Right:
					entity->setPositionX(collisionEntityArea.getLeft() + collisionEntityArea.getWidth());
					entity->entityCollision(*collisionEntity, Sides::Right);
					break;
				default:
					break;
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

CollisionModule::CollisionSide CollisionModule::checkCollisionSide(const FloatArea& areaA, const FloatArea& areaB) const noexcept
{
	const auto centerA = areaA.getCenter();
	const auto centerB = areaB.getCenter();

	const auto isTopCollision = centerA.getY() < centerB.getY() &&
								centerA.getY() < areaB.getTop();
	const auto isBottomCollision = centerA.getY() > areaB.getBottom();

	if (isTopCollision)
	{
		return CollisionSide::Top;
	}
	else if(isBottomCollision)
	{
		return CollisionSide::Bottom;
	}
		
	const auto isLeftCollision = centerA.getX() < centerB.getX() &&
								 centerA.getY() > areaB.getTop();
	const auto isRightCollision = centerA.getY() > areaB.getTop() &&
								  centerA.getY() < areaB.getBottom();

	if (isLeftCollision)
	{
		return CollisionSide::Left;
	}

	if (isRightCollision)
	{
		return CollisionSide::Right;
	}
	
	return CollisionSide::None;
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
