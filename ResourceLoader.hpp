#pragma once

#include <memory>
#include <stdexcept>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

class ResourceLoader final
{
public:
	static std::unique_ptr<sf::Font> loadFont(const std::string& filename);
	static std::unique_ptr<sf::Texture> loadTexture(const std::string& filename);
};

