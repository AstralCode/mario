#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "ResourceIdentifiers.hpp"

class ResourceContainer final
{
public:
	void addFont(const FontIdentifiers identifier, std::unique_ptr<sf::Font> resource) noexcept;
	void addTexture(const TextureIdentifiers identifier, std::unique_ptr<sf::Texture> resource) noexcept;

	const sf::Font& getFont(const FontIdentifiers identifier) const;
	const sf::Texture& getTexture(const TextureIdentifiers identifier) const;

private:
	std::map<FontIdentifiers, std::unique_ptr<sf::Font>> mFonts;
	std::map<TextureIdentifiers, std::unique_ptr<sf::Texture>> mTextures;
};
