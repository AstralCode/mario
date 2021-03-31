#include "EntityContainer.hpp"

#include <algorithm>
#include <functional>

EntityContainer::EntityContainer(GraphicsItem& layer, World& world) noexcept :
	mSceneLayer{layer},
	mWorld{world}
{

}

void EntityContainer::clean() noexcept
{
	auto entitiesIterator = std::remove_if(mEntities.begin(), mEntities.end(), std::mem_fn(&Entity::isDestroyed));
	mEntities.erase(entitiesIterator, mEntities.end());
}


EntityContainer::Iterator EntityContainer::begin() noexcept
{
	return mEntities.begin();
}


EntityContainer::Iterator EntityContainer::end() noexcept
{
	return mEntities.end();
}


EntityContainer::ConstIterator EntityContainer::begin() const noexcept
{
	return mEntities.begin();
}


EntityContainer::ConstIterator EntityContainer::end() const noexcept
{
	return mEntities.end();
}


EntityContainer::ConstIterator EntityContainer::cbegin() const noexcept
{
	return mEntities.cbegin();
}


EntityContainer::ConstIterator EntityContainer::cend() const noexcept
{
	return mEntities.cend();
}
