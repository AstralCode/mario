#pragma once

#include "GameResourceIdentifiers.hpp"

namespace sf
{
class Font;
class Texture;
}

class GameResourceContainer
{
public:
	virtual ~GameResourceContainer() = default;

	virtual const sf::Font& getFont(const FontIdentifiers identifier) const = 0;
	virtual const sf::Texture& getTexture(const TextureIdentifiers identifier) const = 0;
};
