#pragma once

#include "GameObjectIdentifiers.hpp"

class GameObject;

class GameObjectCreator
{
public:
	virtual ~GameObjectCreator() = default;

	virtual GameObject* create(const GameObjectIdentifiers identifier) noexcept = 0;
};