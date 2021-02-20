#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

#include "GameObject.hpp"
#include "GamePhysics.hpp"

GameObjectManager::GameObjectManager(GraphicsItem& graphicsScene, GamePhysics& physics) :
	mGraphicsScene{graphicsScene},
	mGamePhysics{physics}
{

}

GameObject* GameObjectManager::create()
{
	auto object = mGraphicsScene.addItem<GameObject>();
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
	//checkCollisions();

	for (auto& object : mGameObjects)
	{
		object->update(frameTime);
		mGamePhysics.update(*object, frameTime);
	}
}

void GameObjectManager::checkCollisions() const
{
	std::vector<GameObject*> objects = mGameObjects;

	for (auto objectsIterator = objects.begin(); objectsIterator != objects.end();)
	{
		auto objectAdvanceIterator = std::next(objectsIterator, 1u);

		if (objectAdvanceIterator != objects.end())
		{
			if ((*objectsIterator)->isIntersectsItem(*(*objectAdvanceIterator)))
			{

			}
		}
	}
}
