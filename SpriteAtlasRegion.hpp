#pragma once

#include <vector>

#include "SFML/Graphics/Rect.hpp"

class SpriteAtlasRegion final
{
public:
	SpriteAtlasRegion(const sf::Vector2i& offset = {}, const std::vector<std::vector<sf::IntRect>>&areas = {});

	void setOffset(const sf::Vector2i& offset);
	void setSpriteAreas(const std::vector<std::vector<sf::IntRect>>& areas);

	const sf::Vector2i& getOffset() const;
	const std::vector<std::vector<sf::IntRect>>& getSpriteAreas() const;

	int getSpriteAreaCount() const;

private:
	sf::Vector2i mOffset;
	std::vector<std::vector<sf::IntRect>> mSpriteAreas;
};
