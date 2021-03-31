#pragma once

#include "Entity.hpp"

class World;

class EntityContainer final
{
	using Container = std::vector<Entity*>;

public:
	using Iterator = Container::iterator;
	using ConstIterator = Container::const_iterator;

	EntityContainer(GraphicsItem& layer, World& world) noexcept;

	template <typename TEntity>
	TEntity* create() noexcept;

	void clean() noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;

	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;

	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;

private:
	GraphicsItem& mSceneLayer;
	World& mWorld;
	Container mEntities;
};

template <typename TEntity>
TEntity* EntityContainer::create() noexcept
{
	static_assert(std::is_base_of_v<Entity, TEntity>, "TEntity must derived from Entity class");

	auto entity = mSceneLayer.addItem<TEntity>(mWorld);
	mEntities.push_back(entity);

	return entity;
}
