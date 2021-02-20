#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

#include "GameObject.hpp"
#include "GamePhysics.hpp"

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
	checkCollisions();

	for (auto& object : mGameObjects)
	{
		object->update(frameTime);
		mGamePhysics.update(*object, frameTime);
	}
}

void GameObjectManager::checkCollisions() const
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
					collisionHandler->onCollision(object, nextObject);
				}
			}
		}
	}
}
