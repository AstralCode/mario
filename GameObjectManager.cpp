#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

#include "GameObject.hpp"
#include "GamePhysics.hpp"

GameObjectManager::GameObjectManager(GraphicsItem& graphicsScene, GamePhysics& physics, CollisionModule& collisionModule) noexcept :
	mGraphicsScene{graphicsScene},
	mGamePhysics{physics},
	mCollisionModule{collisionModule}
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

	mCollisionModule.execute(mGameObjects);
}
