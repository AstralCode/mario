#include "CollisionModule.hpp"

#include "TilemapView.hpp"

CollisionModule::CollisionModule(TilemapView& tilemapView) noexcept :
	mTilemapView{tilemapView}
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

		auto tileRowCount = 2;
		auto tileColumnCount = 2;

		auto objectTileIndex = mTilemapView.getTileIndex(objectArea.getTopLeft());
		if (objectTileIndex.row > 0)
		{
			objectTileIndex.row -= 1;
			tileRowCount += 1;
		}

		if (objectTileIndex.column > 0)
		{
			objectTileIndex.column -= 1;
			tileColumnCount += 1;
		}

		const auto tilemapRowCount = mTilemapView.getRowCount();
		const auto tilemapColumnCount = mTilemapView.getColumnCount();

		for (auto rowIndex{0}; rowIndex < tileRowCount; rowIndex++)
		{
			TileIndex collideTileIndex{};

			collideTileIndex.row = objectTileIndex.row + rowIndex;
			if (collideTileIndex.row < tilemapRowCount )
			{
				for (auto columnIndex{0}; columnIndex < tileColumnCount; columnIndex++)
				{
					collideTileIndex.column = objectTileIndex.column + columnIndex;
					if (collideTileIndex.column < tilemapColumnCount)
					{
						if (objectTileIndex.row != collideTileIndex.row || objectTileIndex.column != collideTileIndex.column)
						{
							const auto tileAttributes = mTilemapView.getAttributes(collideTileIndex);
							if (tileAttributes.has_value())
							{
								if (tileAttributes.value().isSet(TileAttributes::Collider))
								{
									const auto collideTileArea = mTilemapView.getTileArea(collideTileIndex);
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
