#pragma once

#include "ResourceIdentifiers.hpp"

namespace sf
{
class Font;
class Texture;
}

class ResourceContainer
{
public:
	virtual ~ResourceContainer() = default;

	virtual const sf::Font& getFont(const FontIdentifiers identifier) const noexcept = 0;
	virtual const sf::Texture& getTexture(const TextureIdentifiers identifier) const noexcept = 0;
};
