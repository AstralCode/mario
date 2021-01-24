#pragma once

#include "SFML/Graphics/Rect.hpp"

#include "GameResourceIdentifiers.hpp"

class GameObject;

class GameObjectCreator
{
public:
	virtual ~GameObjectCreator() = default;

	virtual GameObject* addObject(const TextureIdentifiers textureIdentifier, const sf::IntRect& textureArea) = 0;
};