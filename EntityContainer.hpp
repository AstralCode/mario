#pragma once

#include <vector>
#include <algorithm>
#include <functional>

#include "Entity.hpp"

class EntityContainer final
{
	using Container = std::vector<Entity*>;

public:
	using Iterator = Container::iterator;
	using ConstIterator = Container::const_iterator;

	EntityContainer(GraphicsItem& layer) noexcept;

	template <typename TEntity, typename... TArguments>
	TEntity* create(TArguments&&... args) noexcept;

	void clean() noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;

	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;

	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;

private:
	GraphicsItem& mSceneLayer;
	Container mEntities;
};

template <typename TEntity, typename... TArguments>
TEntity* EntityContainer::create(TArguments&&... arguments) noexcept
{
	static_assert(std::is_base_of_v<Entity, TEntity>, "TEntity must derived from Entity class");

	auto entity = mSceneLayer.addItem<TEntity>(std::forward<TArguments&&>(arguments)...);
	mEntities.push_back(entity);

	return entity;
}
