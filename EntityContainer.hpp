#pragma once

#include <vector>

#include "Entity.hpp"

class EntityContainer final
{
	using Container = std::vector<Entity*>;

public:
	using Iterator = Container::iterator;
	using ConstIterator = Container::const_iterator;

	EntityContainer(GraphicsItem& sceneRoot) noexcept;

	template <typename TEntity, typename... TArguments>
	Entity* create(TArguments&&... args) noexcept;

	void clean() noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;

	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;

	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;

private:
	GraphicsItem& mSceneRoot;
	Container mEntities;
};

template<typename TEntity, typename... TArguments>
inline Entity* EntityContainer::create(TArguments&&... arguments) noexcept
{
	static_assert(std::is_base_of_v<Entity, TEntity>, "TEntity must derived from Entity class");

	auto entity = mSceneRoot.addItem<TEntity>(std::forward<TArguments&&>(arguments)...);
	mEntities.push_back(entity);

	return entity;
}
