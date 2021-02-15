#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

#include "GraphicsGameObject.hpp"
#include "GamePhysics.hpp"

GameObjectManager::GameObjectManager(GraphicsItem& graphicsScene, GamePhysics& physics) :
	mGraphicsScene{graphicsScene},
	mGamePhysics{physics}
{

}

GameObject* GameObjectManager::create()
{
	auto object = mGraphicsScene.addItem<GraphicsGameObject>();
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
	for (auto& object : mGameObjects)
	{
		if (!object->isDestroyed())
		{
			object->update(frameTime);

			mGamePhysics.update(*object, frameTime);
		}
	}
}
