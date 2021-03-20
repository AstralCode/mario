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

	template <typename T>
	Entity* create() noexcept;

	void clean() noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;

	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;

	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;

private:
	GraphicsItem& mSceneRoot;
	Container mGameObjects;
};

template<typename T>
inline Entity* EntityContainer::create() noexcept
{
	auto object = mSceneRoot.addItem<Entity>();
	mGameObjects.push_back(object);

	return object;
}
