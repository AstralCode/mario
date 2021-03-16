#include "ResourceContainer.hpp"

void ResourceContainer::addFont(const Fonts identifier, std::unique_ptr<sf::Font> resource) noexcept
{
	mFonts.emplace(identifier, std::move(resource));
}

void ResourceContainer::addTexture(const Textures identifier, std::unique_ptr<sf::Texture> resource) noexcept
{
	mTextures.emplace(identifier, std::move(resource));
}

const sf::Font& ResourceContainer::getFont(const Fonts identifier) const
{
	return *mFonts.at(identifier);
}

const sf::Texture& ResourceContainer::getTexture(const Textures identifier) const
{
	return *mTextures.at(identifier);
}
