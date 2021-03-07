#include "CollisionModule.hpp"

#include "GraphicsScene.hpp"

CollisionModule::CollisionModule(TilemapView& tilemapView) noexcept :
	mTilemapView{tilemapView}
{

}

void CollisionModule::detectCollisions(const GameObjectContainer& objects) noexcept
{
	executeTilemapCollisionHandlers(checkTilemapCollisions(objects));
	executeObjectCollisionHandlers(checkObjectCollisions(objects));
}

void CollisionModule::executeTilemapCollisionHandlers(const TilemapColliders& colliders) const noexcept
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

void CollisionModule::executeObjectCollisionHandlers(const ObjectColliders& colliders) const noexcept
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

CollisionModule::TilemapColliders CollisionModule::checkTilemapCollisions(const GameObjectContainer& objects) const noexcept
{
	TilemapColliders colliders{};
	
	const auto tilemapRowCount = mTilemapView.getRowCount();
	const auto tilemapColumnCount = mTilemapView.getColumnCount();

	for (auto object : objects)
	{
		const auto objectArea = object->getArea();

		TileIndex tileCount{2, 2};

		auto objectTileIndex = mTilemapView.getTileIndex(objectArea.getTopLeft());
		if (objectTileIndex.row > 0)
		{
			objectTileIndex.row -= 1;
			tileCount.row += 1;
		}

		if (objectTileIndex.column > 0)
		{
			objectTileIndex.column -= 1;
			tileCount.column += 1;
		}

		for (auto rowIndex{0}; rowIndex < tileCount.row; rowIndex++)
		{
			TileIndex collideTileIndex{};

			collideTileIndex.row = objectTileIndex.row + rowIndex;
			if (collideTileIndex.row < tilemapRowCount)
			{
				for (auto columnIndex{0}; columnIndex < tileCount.column; columnIndex++)
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
									const auto tileArea = mTilemapView.getTileArea(collideTileIndex);
									if (objectArea.isIntersects(tileArea))
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

CollisionModule::ObjectColliders CollisionModule::checkObjectCollisions(const GameObjectContainer& objects) const noexcept
{
	ObjectColliders colliders{};

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
