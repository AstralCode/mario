#pragma once

#include <vector>

#include "GameObject.hpp"

class GameObjectContainer final
{
	using Container = std::vector<GameObject*>;

public:
	using Iterator = Container::iterator;
	using ConstIterator = Container::const_iterator;

	GameObjectContainer(GraphicsItem& sceneRoot) noexcept;

	GameObject* create(const GameObjectIdentifiers identifier) noexcept;

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
