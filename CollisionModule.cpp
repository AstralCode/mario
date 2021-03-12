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
	
	for (auto object : objects)
	{
		const auto tileIndexes = mTilemapView.getOverlapTileIndexes(object->getArea());
		for (const auto& tileIndex : tileIndexes)
		{
			const auto tileAttributes = mTilemapView.getAttributes(tileIndex);
			if (tileAttributes.has_value())
			{
				if (tileAttributes.value().isSet(TileAttributes::Collider))
				{
					const auto tileArea = mTilemapView.getTileArea(tileIndex);
					const auto objectArea = object->getArea();
					if (objectArea.isIntersects(tileArea))
					{
						colliders.emplace_back(object, tileIndex);
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

CollisionSide CollisionModule::checkCollisionSide(const GameObject* objectAlpha, const GameObject* objectBeta) const noexcept
{
	CollisionSide side{CollisionSide::Top};

	TileIndex tileObjectA = mTilemapView.getTileIndex(objectAlpha->getPosition());
	TileIndex tileObjectB = mTilemapView.getTileIndex(objectBeta->getPosition());

	if (tileObjectA.row < tileObjectB.row)
	{

	}

	return side;
}
