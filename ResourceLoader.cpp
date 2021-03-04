#include "ResourceLoader.hpp"

std::unique_ptr<sf::Font> ResourceLoader::loadFont(const std::string& filename)
{
	auto font = std::make_unique<sf::Font>();
	if (!font->loadFromFile(filename))
	{
		throw std::runtime_error("Font resource: \"" + filename + "\" not found!");
	}

    return font;
}

std::unique_ptr<sf::Texture> ResourceLoader::loadTexture(const std::string& filename)
{
	auto texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(filename))
	{
		throw std::runtime_error("Texture resource: \"" + filename + "\" not found!");
	}

    return texture;
}
