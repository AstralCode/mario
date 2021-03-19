#include "CollisionModule.hpp"

#include "TilemapView.hpp"
#include "GameObjectContainer.hpp"

void CollisionModule::detectCollisions(const GameObjectContainer& objects, TilemapView& tilemapView) noexcept
{
	const auto tileColliders = checkTileCollisions(objects, tilemapView);
	const auto objectColliders = checkObjectCollisions(objects);

	executeTileCollisionHandlers(tileColliders);
	executeObjectCollisionHandlers(objectColliders);
}

void CollisionModule::executeTileCollisionHandlers(const TileColliders& colliders) const noexcept
{
	for (auto& [object, tile] : colliders)
	{
		const auto objectArea = object->getArea();

		const auto objectCenterPosition = objectArea.getCenter();
		const auto tilePosition = tile.area.getCenter();

		auto objectPosition = object->getPosition();

		const auto isTopCollision = objectCenterPosition.getY() < tilePosition.getY() &&
									objectCenterPosition.getY() < tile.area.getTop();
		const auto isBottomCollision = objectCenterPosition.getY() > tile.area.getBottom();

		if (isTopCollision)
		{
			objectPosition.setY(tile.area.getTop() - objectArea.getHeight());
			object->onTileTopCollision(tile);
		}
		else if(isBottomCollision)
		{
			objectPosition.setY(tile.area.getBottom() - 1.0f);
			object->onTileBottomCollision(tile);
		}
		
		const auto isLeftCollision = objectCenterPosition.getX() < tilePosition.getX() &&
									 objectCenterPosition.getY() > tile.area.getTop();
		const auto isRightCollision = objectCenterPosition.getY() > tile.area.getTop() &&
									  objectCenterPosition.getY() < tile.area.getBottom();

		if (isLeftCollision && !isBottomCollision)
		{
			objectPosition.setX(tile.area.getLeft() - objectArea.getWidth());
			object->onTileLeftCollision(tile);
		}
		else if (isRightCollision && !isBottomCollision)
		{
			objectPosition.setX(tile.area.getRight() + 1.0f);
			object->onTileRightCollision(tile);
		}

		object->setPosition(objectPosition);
	}
}

void CollisionModule::executeObjectCollisionHandlers(const ObjectColliders& colliders) const noexcept
{
	for (auto& [objectA, objectB] : colliders)
	{
		auto offsetPosition = objectA->getArea().getWidth();

		if (objectA->isMovingRight())
		{
			offsetPosition = -offsetPosition;
		}

		const auto positionX = objectB->getArea().getLeft();
		objectA->setPositionX(positionX + offsetPosition);

		objectA->onObjectCollision(*objectB);
	}
}

CollisionModule::TileColliders CollisionModule::checkTileCollisions(const GameObjectContainer& objects, TilemapView& tilemapView) const noexcept
{
	TileColliders colliders{};
	
	for (auto object : objects)
	{
		bool falling{true};

		const auto objectArea = object->getArea();

		const auto tiles = tilemapView.getOverlapTiles(objectArea);
		for (const auto& tile : tiles)
		{
			if (tile.attributes.isSet(Tile::Attributes::Collider))
			{
				falling = false;

				if (objectArea.isIntersects(tile.area))
				{
					colliders.emplace_back(object, tile);
				}
			}
		}

		if (falling)
		{
			object->onFalling();
		}
	}

	return colliders;
}

CollisionModule::ObjectColliders CollisionModule::checkObjectCollisions(const GameObjectContainer& objects) const noexcept
{
	ObjectColliders colliders{};

	for (auto objectsIterator = objects.cbegin(); objectsIterator != objects.cend(); objectsIterator++)
	{
		auto& object = *objectsIterator;

		for (auto nextObjectsIterator = std::next(objectsIterator, 1u); nextObjectsIterator != objects.cend() && !object->isDestroyed(); nextObjectsIterator++)
		{
			auto& nextObject = *nextObjectsIterator;

			if (object->isIntersectsItem(*nextObject))
			{
				colliders.emplace_back(object, nextObject);
			}
		}
	}

	return colliders;
}
