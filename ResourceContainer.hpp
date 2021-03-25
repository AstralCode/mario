#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "ResourceIdentifiers.hpp"

class ResourceContainer final
{
public:
	void addFont(const FontId identifier, std::unique_ptr<sf::Font> resource) noexcept;
	void addTexture(const TextureId identifier, std::unique_ptr<sf::Texture> resource) noexcept;

	const sf::Font& getFont(const FontId identifier) const;
	const sf::Texture& getTexture(const TextureId identifier) const;

private:
	std::map<FontId, std::unique_ptr<sf::Font>> mFonts;
	std::map<TextureId, std::unique_ptr<sf::Texture>> mTextures;
};
