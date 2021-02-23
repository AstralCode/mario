#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

#include "GameObject.hpp"
#include "GamePhysics.hpp"
#include "Tilemap.hpp"

GameObjectManager::GameObjectManager(Tilemap& tilemap, GraphicsItem& graphicsScene, GamePhysics& physics, SpritesetContainer& spritesetContainer) :
	mTilemap{tilemap},
	mGraphicsScene{graphicsScene},
	mGamePhysics{physics},
	mSpritesetContainer{spritesetContainer}
{

}

GameObject* GameObjectManager::create(const GameObjectIdentifiers identifier)
{
	auto object = mGraphicsScene.addItem<GameObject>(identifier);
	mGameObjects.push_back(object);

    return object;
}

void GameObjectManager::receiveEvents(const sf::Event& event)
{
	for (auto& object : mGameObjects)
	{
		object->receiveEvents(event);
	}
}

void GameObjectManager::clean()
{
	auto gameObjectsIterator = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::mem_fn(&GameObject::isDestroyed));
	mGameObjects.erase(gameObjectsIterator, mGameObjects.end());
}

void GameObjectManager::update(const sf::Time& frameTime)
{
	checkTilemapCollisions();
	checkObjectCollisions();

	for (auto& object : mGameObjects)
	{
		object->update(frameTime);
		mGamePhysics.update(*object, frameTime);
	}
}

void GameObjectManager::checkTilemapCollisions() const
{
	for (auto object : mGameObjects)
	{
		auto objectPosition = object->getGlobalPosition();
		auto objectArea = object->getBounds();

		sf::Vector2u indexCount{2u, 2u};

		auto tileIndex = mTilemap.getGrid().getTileIndex( sf::Vector2f{ objectArea.left, objectArea.top } );
		if (tileIndex.x > 0u)
		{
			tileIndex.x -= 1u;
			indexCount.x += 1u;
		}

		if (tileIndex.y > 0u)
		{
			tileIndex.y -= 1u;
			indexCount.y += 1u;
		}

		auto& tilemapCount = mTilemap.getTileCount();

		for (sf::Vector2u index{}; index.y < indexCount.y; index.y++)
		{
			const auto y = tileIndex.y + index.y;

			if (y < tilemapCount.y)
			{
				for (index.x = 0u; index.x < indexCount.x; index.x++)
				{
					const auto x = tileIndex.x + index.x;

					if (x < tilemapCount.x)
					{
						auto tileArea = mTilemap.getGrid().getTileArea({x, y});
						if (objectArea.intersects(tileArea))
						{
							const auto tileIdentifier = mTilemap.getTileIdentifier({x, y});
							if (tileIdentifier > 0u)
							{
								auto collisionHandlerIterator = mCollisionHandlers.find(object->getIdentifier());
								if (collisionHandlerIterator != mCollisionHandlers.end())
								{
									auto& collisionHandler = collisionHandlerIterator->second;
									collisionHandler->onTileCollision(object, tileIdentifier);
								}
							}
						}
					}
				}
			}
		}
	}
}

void GameObjectManager::checkObjectCollisions() const
{
	std::vector<GameObject*> objects = mGameObjects;

	for (auto objectsIterator = objects.begin(); objectsIterator != objects.end(); objectsIterator++)
	{
		auto& object = *objectsIterator;

		for (auto nextObjectIterator = std::next(objectsIterator, 1u); nextObjectIterator != objects.end() && !object->isDestroyed(); nextObjectIterator++)
		{
			auto& nextObject = *nextObjectIterator;

			if (object->isIntersectsItem(*nextObject))
			{
				auto collisionHandlerIterator = mCollisionHandlers.find(object->getIdentifier());
				if (collisionHandlerIterator != mCollisionHandlers.end())
				{
					auto& collisionHandler = collisionHandlerIterator->second;
					collisionHandler->onObjectCollision(object, nextObject);
				}
			}
		}
	}
}
