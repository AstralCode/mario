#pragma once

#include <string>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "GameResourceIdentifiers.hpp"

class GameResourceManager final : private sf::NonCopyable
{
public:
	void AddFontResource(const FontResourceIdentifiers fontResourceIdentifier, std::string_view fontResourceFilename);
	sf::Font GetFontResource(const FontResourceIdentifiers fontResourceIdentifier) const;

	void AddTextureResource(const TextureResourceIdentifiers textureResourceIdentifier, std::string_view textureResourceFilename);
	sf::Texture GetTextureResource(const TextureResourceIdentifiers textureResourceIdentifier) const;
};
