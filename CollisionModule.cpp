#include "CollisionModule.hpp"

#include "GraphicsScene.hpp"

CollisionModule::CollisionModule(GraphicsScene& scene) noexcept :
	mScene{scene}
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

	for (auto object : objects)
	{
		const auto objectPosition = object->getGlobalPosition();
		const auto objectArea = object->getArea();

		auto tileRowCount = 2;
		auto tileColumnCount = 2;

		auto objectTileIndex = mScene.getTilemapView().getTileIndex(objectArea.getTopLeft());
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

		const auto tilemapRowCount = mScene.getTilemapView().getRowCount();
		const auto tilemapColumnCount = mScene.getTilemapView().getColumnCount();

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
							const auto tileAttributes = mScene.getTilemapView().getAttributes(collideTileIndex);
							if (tileAttributes.has_value())
							{
								if (tileAttributes.value().isSet(TileAttributes::Collider))
								{
									const auto collideTileArea = mScene.getTilemapView().getTileArea(collideTileIndex);
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
