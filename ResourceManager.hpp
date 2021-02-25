#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "ResourceContainer.hpp"

class ResourceManager final : public ResourceContainer
{
public:
	void addFont(const FontIdentifiers identifier, const std::string& filename) noexcept;
	void addTexture(const TextureIdentifiers identifier, const std::string& filename) noexcept;

	const sf::Font& getFont(const FontIdentifiers identifier) const noexcept override;
	const sf::Texture& getTexture(const TextureIdentifiers identifier) const noexcept override;

private:
	std::map<FontIdentifiers, std::unique_ptr<sf::Font>> mFonts;
	std::map<TextureIdentifiers, std::unique_ptr<sf::Texture>> mTextures;
};
