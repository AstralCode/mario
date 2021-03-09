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
		const auto objectTileIndex = mTilemapView.getTileIndex(object->getGlobalPosition());

		TileIndex tileIndex{};

		for (auto rowIndex{0}; rowIndex < 3; rowIndex++)
		{
			tileIndex.row = objectTileIndex.row + (-1 + rowIndex);
			if (tileIndex.row >= 0 && tileIndex.row < tilemapRowCount)
			{
				for (auto columnIndex{0}; columnIndex < 3; columnIndex++)
				{
					tileIndex.column = objectTileIndex.column + (-1 + columnIndex);
					if (tileIndex.column >= 0 && tileIndex.column < tilemapColumnCount)
					{
						if (objectTileIndex != tileIndex)
						{
							const auto tileAttributes = mTilemapView.getAttributes(tileIndex);
							if (tileAttributes.has_value())
							{
								if (tileAttributes.value().isSet(TileAttributes::Collider))
								{
									const auto objectArea = object->getArea();
									const auto tileArea = mTilemapView.getTileArea(tileIndex);
									if (objectArea.isIntersects(tileArea))
									{
										colliders.emplace_back(object, tileIndex);
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

CollisionSide CollisionModule::checkCollisionSide(const GameObject* objectAlpha, const GameObject* objectBeta) const noexcept
{
	CollisionSide side{CollisionSide::Top};

	TileIndex tileObjectA = mTilemapView.getTileIndex(objectAlpha->getGlobalPosition());
	TileIndex tileObjectB = mTilemapView.getTileIndex(objectBeta->getGlobalPosition());

	if (tileObjectA.row < tileObjectB.row)
	{

	}

	return side;
}
