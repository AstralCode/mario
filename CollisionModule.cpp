#include "CollisionModule.hpp"

#include "Tilemap.hpp"

CollisionModule::CollisionModule(Tilemap& tilemap) noexcept :
	mTilemap{tilemap}
{

}

void CollisionModule::execute(const std::vector<GameObject*> objects) noexcept
{
	executeTilemapCollisionHandlers(checkTilemapCollisions(objects));
	executeObjectCollisionHandlers(checkObjectCollisions(objects));
}

void CollisionModule::executeTilemapCollisionHandlers(const std::vector<TilemapColliders>& colliders) const noexcept
{
	for (auto& [object, tileIndex] : colliders)
	{
		for (auto& collisionHandler : mCollisionHandlers)
		{
			if (collisionHandler->isSetTarget(object->getIdentifier()))
			{
				collisionHandler->onTileCollision(object, tileIndex);
			}
		}
	}
}

void CollisionModule::executeObjectCollisionHandlers(const std::vector<ObjectColliders>& colliders) const noexcept
{
	for (auto& [target, object] : colliders)
	{
		for (auto& collisionHandler : mCollisionHandlers)
		{
			if (collisionHandler->isSetTarget(target->getIdentifier()))
			{
				collisionHandler->onObjectCollision(target, object);
			}
		}
	}
}

std::vector<CollisionModule::TilemapColliders> CollisionModule::checkTilemapCollisions(const std::vector<GameObject*> objects) const noexcept
{
	std::vector<TilemapColliders> colliders{};

	for (auto object : objects)
	{
		const auto objectPosition = object->getGlobalPosition();
		const auto objectArea = object->getArea();

		auto tileColumnCount = 2;
		auto tileRowCount = 2;

		auto objectTileIndex = mTilemap.getGrid().getTileIndex(objectArea.getTopLeft());
		if (objectTileIndex.row > 0u)
		{
			objectTileIndex.row -= 1u;
			tileRowCount += 1u;
		}

		if (objectTileIndex.column > 0u)
		{
			objectTileIndex.column -= 1u;
			tileColumnCount += 1u;
		}

		const auto tilemapRowCount = mTilemap.getTileRowCount();
		const auto tilemapColumnCount = mTilemap.getTileColumnCount();

		for (auto columnIndex{0}; columnIndex < tileColumnCount; columnIndex++)
		{
			TileIndex collideTileIndex{};

			collideTileIndex.column = objectTileIndex.column + columnIndex;
			if (collideTileIndex.column < tilemapColumnCount)
			{
				for (auto rowIndex{0}; rowIndex < tileRowCount; rowIndex++)
				{
					collideTileIndex.row = objectTileIndex.row + rowIndex;
					if (collideTileIndex.row < tilemapRowCount)
					{
						if (objectTileIndex.row != collideTileIndex.row || objectTileIndex.column != collideTileIndex.column)
						{
							const auto tileAttributes = mTilemap.getTileAttributes(collideTileIndex);
							if (tileAttributes.has_value())
							{
								if (tileAttributes.value().isSet(TileAttributes::Collider))
								{
									const auto collideTileArea = mTilemap.getGrid().getTileArea(collideTileIndex);
									if (objectArea.isIntersects(collideTileArea))
									{
										colliders.emplace_back(object, collideTileIndex);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return colliders;
}

std::vector<CollisionModule::ObjectColliders> CollisionModule::checkObjectCollisions(const std::vector<GameObject*> objects) const noexcept
{
	std::vector<ObjectColliders> colliders{};

	for (auto objectsIterator = objects.cbegin(); objectsIterator != objects.cend(); objectsIterator++)
	{
		auto& object = *objectsIterator;

		for (auto nextObjectIterator = std::next(objectsIterator, 1u); nextObjectIterator != objects.cend() && !object->isDestroyed(); nextObjectIterator++)
		{
			auto& nextObject = *nextObjectIterator;

			if (object->isIntersectsItem(*nextObject))
			{
				colliders.emplace_back(object, nextObject);
			}
		}
	}

	return colliders;
}
