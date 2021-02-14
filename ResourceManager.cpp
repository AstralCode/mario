#include "ResourceManager.hpp"

void ResourceManager::addFont(const FontIdentifiers identifier, const std::string& filename)
{
	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(filename))
	{
		mFonts.emplace(identifier, std::move(font));
	}
}

void ResourceManager::addTexture(const TextureIdentifiers identifier, const std::string& filename)
{
	auto texture = std::make_unique<sf::Texture>();

	if (texture->loadFromFile(filename))
	{
		mTextures.emplace(identifier, std::move(texture));
	}
}

const sf::Font& ResourceManager::getFont(const FontIdentifiers identifier) const
{
	return *mFonts.at(identifier);
}

const sf::Texture& ResourceManager::getTexture(const TextureIdentifiers identifier) const
{
	return *mTextures.at(identifier);
}
