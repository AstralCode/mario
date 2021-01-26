#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

GameObject* GameObjectManager::create(GraphicsSpriteItem* sprite)
{
	auto object = std::make_unique<GameObject>(sprite);
	auto objectPointer = object.get();

	mGameObjects.push_back(std::move(object));

    return objectPointer;
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
		object->update(frameTime);
	}
}
