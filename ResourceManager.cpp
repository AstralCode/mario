#include "ResourceManager.hpp"

bool ResourceManager::loadFont(const FontIdentifiers identifier, const std::string& filename) noexcept
{
	auto font = std::make_unique<sf::Font>();
	if (!font->loadFromFile(filename))
	{
		return false;
	}

	mFonts.emplace(identifier, std::move(font));

	return true;
}

bool ResourceManager::loadTexture(const TextureIdentifiers identifier, const std::string& filename) noexcept
{
	auto texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(filename))
	{
		return false;
	}

	mTextures.emplace(identifier, std::move(texture));

	return true;
}

const sf::Font& ResourceManager::getFont(const FontIdentifiers identifier) const noexcept
{
	return *mFonts.at(identifier);
}

const sf::Texture& ResourceManager::getTexture(const TextureIdentifiers identifier) const noexcept
{
	return *mTextures.at(identifier);
}
