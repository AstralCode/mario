#include "ResourceContainer.hpp"

void ResourceContainer::addFont(const FontId identifier, std::unique_ptr<sf::Font> resource) noexcept
{
	mFonts.emplace(identifier, std::move(resource));
}

void ResourceContainer::addTexture(const TextureId identifier, std::unique_ptr<sf::Texture> resource) noexcept
{
	mTextures.emplace(identifier, std::move(resource));
}

const sf::Font& ResourceContainer::getFont(const FontId identifier) const
{
	return *mFonts.at(identifier);
}

const sf::Texture& ResourceContainer::getTexture(const TextureId identifier) const
{
	return *mTextures.at(identifier);
}
