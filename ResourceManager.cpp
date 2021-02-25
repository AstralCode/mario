#include "ResourceManager.hpp"

void ResourceManager::addFont(const FontIdentifiers identifier, const std::string& filename) noexcept
{
	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(filename))
	{
		mFonts.emplace(identifier, std::move(font));
	}
}

void ResourceManager::addTexture(const TextureIdentifiers identifier, const std::string& filename) noexcept
{
	auto texture = std::make_unique<sf::Texture>();

	if (texture->loadFromFile(filename))
	{
		mTextures.emplace(identifier, std::move(texture));
	}
}

const sf::Font& ResourceManager::getFont(const FontIdentifiers identifier) const noexcept
{
	return *mFonts.at(identifier);
}

const sf::Texture& ResourceManager::getTexture(const TextureIdentifiers identifier) const noexcept
{
	return *mTextures.at(identifier);
}
