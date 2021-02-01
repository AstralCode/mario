#pragma once

#include <vector>

#include "SFML/Graphics/Rect.hpp"

class SpriteAtlasRegion final
{
public:
	SpriteAtlasRegion(const sf::Vector2i& offset, const sf::Vector2i& spriteSize, const std::vector<std::vector<sf::IntRect>>& spriteAreas);

	const sf::IntRect& getSprite(const int index) const;

	int getSpriteCount() const;

private:
	void calculateSpriteAreas(const sf::Vector2i& offset, const sf::Vector2i& spriteSize, const std::vector<std::vector<sf::IntRect>>& spriteAreas);

	std::vector<sf::IntRect> mSprites;
};
