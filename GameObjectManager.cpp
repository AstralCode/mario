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

	mGraphicsScene.clean();
}

void GameObjectManager::update(const sf::Time& frameTime)
{
	executeTilemapCollisionHandlers(checkTilemapCollisions());
	executeObjectCollisionHandlers(checkObjectCollisions());

	for (auto& object : mGameObjects)
	{
		object->update(frameTime);
		mGamePhysics.update(*object, frameTime);
	}
}

void GameObjectManager::executeTilemapCollisionHandlers(const std::vector<std::tuple<GameObject*, sf::Vector2u>>& colliders) const
{
	for (auto& [object, tileIndex] : colliders)
	{
		auto collisionHandlerIterator = mCollisionHandlers.find(object->getIdentifier());
		if ( collisionHandlerIterator != mCollisionHandlers.end() )
		{
			return collisionHandlerIterator->second->onTileCollision(object, tileIndex);
		}
	}
}

void GameObjectManager::executeObjectCollisionHandlers(const std::vector<std::tuple<GameObject*, GameObject*>>& colliders) const
{
	for (auto& [target, object] : colliders)
	{
		auto collisionHandlerIterator = mCollisionHandlers.find(object->getIdentifier());
		if (collisionHandlerIterator != mCollisionHandlers.end())
		{
			return collisionHandlerIterator->second->onObjectCollision(target, object);
		}
	}
}

std::vector<std::tuple<GameObject*, sf::Vector2u>> GameObjectManager::checkTilemapCollisions() const
{
	std::vector<std::tuple<GameObject*, sf::Vector2u>> colliders{};

	for (auto object : mGameObjects)
	{
		const auto objectPosition = object->getGlobalPosition();
		const auto objectArea = object->getBounds();

		sf::Vector2u indexCount{2u, 2u};

		auto tileIndex = mTilemap.getGrid().getTileIndex(sf::Vector2f{objectArea.left, objectArea.top});
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
						const auto tileIdentifier = mTilemap.getTileIdentifier({x, y});
						if (tileIdentifier > 0u)
						{
							auto tileArea = mTilemap.getGrid().getTileArea({x, y});
							if (objectArea.intersects(tileArea))
							{
								colliders.emplace_back(object, sf::Vector2u{x, y});
							}
						}
					}
				}
			}
		}
	}

	return colliders;
}

std::vector<std::tuple<GameObject*, GameObject*>> GameObjectManager::checkObjectCollisions() const
{
	std::vector<std::tuple<GameObject*, GameObject*>> colliders{};

	std::vector<GameObject*> objects = mGameObjects;

	for (auto objectsIterator = objects.begin(); objectsIterator != objects.end(); objectsIterator++)
	{
		auto& object = *objectsIterator;

		for (auto nextObjectIterator = std::next(objectsIterator, 1u); nextObjectIterator != objects.end() && !object->isDestroyed(); nextObjectIterator++)
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
