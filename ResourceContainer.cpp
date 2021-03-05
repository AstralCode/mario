#include "ResourceContainer.hpp"

void ResourceContainer::addFont(const FontIdentifiers identifier, std::unique_ptr<sf::Font> resource) noexcept
{
	mFonts.emplace(identifier, std::move(resource));
}

void ResourceContainer::addTexture(const TextureIdentifiers identifier, std::unique_ptr<sf::Texture> resource) noexcept
{
	mTextures.emplace(identifier, std::move(resource));
}

const sf::Font& ResourceContainer::getFont(const FontIdentifiers identifier) const
{
	return *mFonts.at(identifier);
}

const sf::Texture& ResourceContainer::getTexture(const TextureIdentifiers identifier) const
{
	return *mTextures.at(identifier);
}
