#include "GameObjectContainer.hpp"

#include <algorithm>
#include <functional>

GameObjectContainer::GameObjectContainer(GraphicsItem& sceneRoot) noexcept :
	mSceneRoot{sceneRoot}
{

}

GameObject* GameObjectContainer::create(const GameObjectIdentifiers identifier) noexcept
{
	auto object = mSceneRoot.addItem<GameObject>(identifier);
	mGameObjects.push_back(object);

	return object;
}

void GameObjectContainer::clean() noexcept
{
	auto gameObjectsIterator = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::mem_fn(&GameObject::isDestroyed));
	mGameObjects.erase(gameObjectsIterator, mGameObjects.end());
}

GameObjectContainer::Iterator GameObjectContainer::begin() noexcept
{
	return mGameObjects.begin();
}

GameObjectContainer::Iterator GameObjectContainer::end() noexcept
{
	return mGameObjects.end();
}

GameObjectContainer::ConstIterator GameObjectContainer::begin() const noexcept
{
	return mGameObjects.begin();
}

GameObjectContainer::ConstIterator GameObjectContainer::end() const noexcept
{
	return mGameObjects.end();
}

GameObjectContainer::ConstIterator GameObjectContainer::cbegin() const noexcept
{
	return mGameObjects.cbegin();
}

GameObjectContainer::ConstIterator GameObjectContainer::cend() const noexcept
{
	return mGameObjects.cend();
}
