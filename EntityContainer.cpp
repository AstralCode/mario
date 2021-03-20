#include "EntityContainer.hpp"

#include <algorithm>
#include <functional>

EntityContainer::EntityContainer(GraphicsItem& sceneRoot) noexcept :
	mSceneRoot{sceneRoot}
{

}

void EntityContainer::clean() noexcept
{
	auto gameObjectsIterator = std::remove_if(mGameObjects.begin(), mGameObjects.end(), std::mem_fn(&Entity::isDestroyed));
	mGameObjects.erase(gameObjectsIterator, mGameObjects.end());
}

EntityContainer::Iterator EntityContainer::begin() noexcept
{
	return mGameObjects.begin();
}

EntityContainer::Iterator EntityContainer::end() noexcept
{
	return mGameObjects.end();
}

EntityContainer::ConstIterator EntityContainer::begin() const noexcept
{
	return mGameObjects.begin();
}

EntityContainer::ConstIterator EntityContainer::end() const noexcept
{
	return mGameObjects.end();
}

EntityContainer::ConstIterator EntityContainer::cbegin() const noexcept
{
	return mGameObjects.cbegin();
}

EntityContainer::ConstIterator EntityContainer::cend() const noexcept
{
	return mGameObjects.cend();
}
