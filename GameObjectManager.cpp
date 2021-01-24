#include "GameObjectManager.hpp"

#include <algorithm>
#include <functional>

GameObjectManager::GameObjectManager(GraphicsItem& graphicsScene) :
	mGraphicsScene{graphicsScene}
{

}

GameObject* GameObjectManager::create()
{
	auto gameObjectSprite = mGraphicsScene.addItem<GraphicsSpriteItem>();

	auto gameObject = std::make_unique<GameObject>(gameObjectSprite);
	auto gameObjectPointer = gameObject.get();

	mGameObjects.push_back(std::move(gameObject));

    return gameObjectPointer;
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
