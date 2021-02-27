#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

#include "GameObject.hpp"
#include "GamePhysics.hpp"
#include "Tilemap.hpp"

GameObjectManager::GameObjectManager(Tilemap& tilemap, GraphicsItem& graphicsScene, GamePhysics& physics, SpritesetContainer& spritesetContainer) noexcept :
	mTilemap{tilemap},
	mGraphicsScene{graphicsScene},
	mGamePhysics{physics},
	mSpritesetContainer{spritesetContainer}
{

}

GameObject* GameObjectManager::create(const GameObjectIdentifiers identifier) noexcept
{
	auto object = mGraphicsScene.addItem<GameObject>(identifier);
	mGameObjects.push_back(object);

    return object;
}

void GameObjectManager::receiveEvents(const sf::Event& event) noexcept
{
	for (auto& object : mGameObjects)
	{
		object->receiveEvents(event);
	}
}

void GameObjectManager::clean() noexcept
{
	auto gameObjectsIterator = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::mem_fn(&GameObject::isDestroyed));
	mGameObjects.erase(gameObjectsIterator, mGameObjects.end());

	mGraphicsScene.clean();
}

void GameObjectManager::update(const sf::Time& frameTime) noexcept
{
	for (auto& object : mGameObjects)
	{
		object->update(frameTime);
		mGamePhysics.update(*object, frameTime);
	}

	executeTilemapCollisionHandlers(checkTilemapCollisions());
	executeObjectCollisionHandlers(checkObjectCollisions());
}

void GameObjectManager::executeTilemapCollisionHandlers(const std::vector<TilemapColliders>& colliders) const noexcept
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

void GameObjectManager::executeObjectCollisionHandlers(const std::vector<ObjectColliders>& colliders) const noexcept
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

std::vector<GameObjectManager::TilemapColliders> GameObjectManager::checkTilemapCollisions() const noexcept
{
	std::vector<TilemapColliders> colliders{};

	for (auto object : mGameObjects)
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

std::vector<GameObjectManager::ObjectColliders> GameObjectManager::checkObjectCollisions() const noexcept
{
	std::vector<ObjectColliders> colliders{};

	for (auto objectsIterator = mGameObjects.cbegin(); objectsIterator != mGameObjects.cend(); objectsIterator++)
	{
		auto& object = *objectsIterator;

		for (auto nextObjectIterator = std::next(objectsIterator, 1u); nextObjectIterator != mGameObjects.cend() && !object->isDestroyed(); nextObjectIterator++)
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
