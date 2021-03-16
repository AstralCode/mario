#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Resources.hpp"

class ResourceContainer final
{
public:
	void addFont(const Fonts identifier, std::unique_ptr<sf::Font> resource) noexcept;
	void addTexture(const Textures identifier, std::unique_ptr<sf::Texture> resource) noexcept;

	const sf::Font& getFont(const Fonts identifier) const;
	const sf::Texture& getTexture(const Textures identifier) const;

private:
	std::map<Fonts, std::unique_ptr<sf::Font>> mFonts;
	std::map<Textures, std::unique_ptr<sf::Texture>> mTextures;
};
