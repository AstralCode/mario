#pragma once

#include <vector>

#include "SFML/Graphics/Rect.hpp"

class SpriteAtlasRegion final
{
public:
	SpriteAtlasRegion(const sf::Vector2i& offset, const sf::Vector2i& spriteSize, const std::vector<std::vector<sf::IntRect>>& areas);

	const sf::IntRect& getSprite(const int index) const;

	int getSpriteCount() const;

private:
	void initializeSpriteAreas(const sf::Vector2i& offset, const sf::Vector2i& spriteSize, const std::vector<std::vector<sf::IntRect>>& areas);

	std::vector<sf::IntRect> mSpriteAreas;
};
