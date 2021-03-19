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
		auto objectPosition = object->getPosition();

		const auto objectArea = object->getArea();

		const auto collisionSide = checkCollisionSide(objectArea, tile.area);
		switch (collisionSide)
		{
			case Side::Top:
				objectPosition.setY(tile.area.getTop() - objectArea.getHeight());
				object->onTileTopCollision(tile);
				break;
			case Side::Bottom:
				objectPosition.setY(tile.area.getBottom() - 1.0f);
				object->onTileBottomCollision(tile);
				break;
			case Side::Left:
				objectPosition.setX(tile.area.getLeft() - objectArea.getWidth());
				object->onTileLeftCollision(tile);
				break;
			case Side::Right:
				objectPosition.setX(tile.area.getRight() + 1.0f);
				object->onTileRightCollision(tile);
				break;
			default:
				break;
		}

		if (collisionSide != Side::None)
		{
			object->setPosition(objectPosition);
		}
	}
}

void CollisionModule::executeObjectCollisionHandlers(const ObjectColliders& colliders) const noexcept
{
	for (auto& [objectA, objectB] : colliders)
	{
		const auto objectAArea = objectA->getArea();
		const auto objectBArea = objectB->getArea();

		const auto positionX = objectBArea.getLeft();
		auto offsetPosition{0.0f};

		const auto collisionSide = checkCollisionSide(objectAArea, objectBArea);
		switch (collisionSide)
		{
			case Side::Top:

				break;
			case Side::Bottom:
				break;
			case Side::Left:
				offsetPosition = -objectAArea.getWidth();
				break;
			case Side::Right:
				offsetPosition = objectBArea.getWidth();
				break;
			default:
				break;
		}

		if (collisionSide != Side::None)
		{
			objectA->setPositionX(positionX + offsetPosition);
			objectA->onObjectCollision(*objectB);
		}
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

CollisionModule::Side CollisionModule::checkCollisionSide(const FloatArea& areaA, const FloatArea& areaB) const noexcept
{
	const auto centerA = areaA.getCenter();
	const auto centerB = areaB.getCenter();

	const auto isTopCollision = centerA.getY() < centerB.getY() &&
								centerA.getY() < areaB.getTop();
	const auto isBottomCollision = centerA.getY() > areaB.getBottom();

	if (isTopCollision)
	{
		return Side::Top;
	}
	else if(isBottomCollision)
	{
		return Side::Bottom;
	}
		
	const auto isLeftCollision = centerA.getX() < centerB.getX() &&
								 centerA.getY() > areaB.getTop();
	const auto isRightCollision = centerA.getY() > areaB.getTop() &&
								  centerA.getY() < areaB.getBottom();

	if (isLeftCollision)
	{
		return Side::Left;
	}

	if (isRightCollision)
	{
		return Side::Right;
	}
	
	return Side::None;
}
