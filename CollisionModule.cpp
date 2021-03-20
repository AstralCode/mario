#include "CollisionModule.hpp"

#include "TilemapView.hpp"
#include "EntityContainer.hpp"

void CollisionModule::detectCollisions(const EntityContainer& entities, TilemapView& tilemapView) noexcept
{
	const auto tileColliders = checkTileCollisions(entities, tilemapView);
	const auto entityColliders = checkEntityCollisions(entities);

	executeTileCollisionHandlers(tileColliders);
	executeEntityCollisionHandlers(entityColliders);
}

void CollisionModule::executeTileCollisionHandlers(const TileColliders& colliders) const noexcept
{
	for (auto& [entity, tile] : colliders)
	{
		auto entityPosition = entity->getPosition();

		const auto entityArea = entity->getArea();

		const auto collisionSide = checkCollisionSide(entityArea, tile.area);
		switch (collisionSide)
		{
			case CollisionSide::Top:
				entityPosition.setY(tile.area.getTop() - entityArea.getHeight());
				entity->tileCollision(tile, Tile::Sides::Top);
				break;
			case CollisionSide::Bottom:
				entityPosition.setY(tile.area.getBottom() - 1.0f);
				entity->tileCollision(tile, Tile::Sides::Bottom);
				break;
			case CollisionSide::Left:
				entityPosition.setX(tile.area.getLeft() - entityArea.getWidth());
				entity->tileCollision(tile, Tile::Sides::Left);
				break;
			case CollisionSide::Right:
				entityPosition.setX(tile.area.getRight() + 1.0f);
				entity->tileCollision(tile, Tile::Sides::Right);
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

void CollisionModule::executeEntityCollisionHandlers(const EntityColliders& colliders) const noexcept
{
	for (auto& [entityA, entityB] : colliders)
	{
		const auto areaA = entityA->getArea();
		const auto areaB = entityB->getArea();

		auto offsetPosition{0.0f};

		const auto collisionSide = checkCollisionSide(areaA, areaB);
		switch (collisionSide)
		{
			case CollisionSide::Top:
				break;
			case CollisionSide::Bottom:
				break;
			case CollisionSide::Left:
				offsetPosition = -areaA.getWidth();
				break;
			case CollisionSide::Right:
				offsetPosition = areaB.getWidth();
				break;
			default:
				break;
		}

		if (collisionSide != CollisionSide::None)
		{
			entityA->setPositionX(areaB.getLeft() + offsetPosition);
			entityA->entityCollision(*entityB);
		}
	}
}

CollisionModule::TileColliders CollisionModule::checkTileCollisions(const EntityContainer& entities, TilemapView& tilemapView) const noexcept
{
	TileColliders colliders{};
	
	for (auto entity : entities)
	{
		bool isEntityFalling{true};

		const auto entityArea = entity->getArea();

		const auto tiles = tilemapView.getOverlapTiles(entityArea);
		for (const auto& tile : tiles)
		{
			if (tile.attributes.isSet(Tile::Attributes::Collider))
			{
				isEntityFalling = false;

				if (entityArea.isIntersects(tile.area))
				{
					colliders.emplace_back(entity, tile);
				}
			}
		}

		if (isEntityFalling)
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
		auto& entityA = *entitiesIterator;

		for (auto nextEntitiesIterator = std::next(entitiesIterator, 1u); nextEntitiesIterator != entities.cend() && !entityA->isDestroyed(); nextEntitiesIterator++)
		{
			auto& entityB = *nextEntitiesIterator;

			if (entityA->isIntersectsItem(*entityB))
			{
				colliders.emplace_back(entityA, entityB);
			}
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
