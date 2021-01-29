#pragma once

#include <vector>

#include "SFML/Graphics/Rect.hpp"

class SpriteAtlasRegion final
{
public:
	void setOffset(const sf::Vector2i& offset);
	void setAreaSize(const sf::Vector2i& size);
	void setSpriteAreas(const std::vector<sf::IntRect>& areas);

	const sf::Vector2i& getOffset() const;
	const sf::Vector2i& getSpriteSize() const;
	const std::vector<sf::IntRect>& getSpriteAreas() const;

private:
	sf::Vector2i mOffset;
	sf::Vector2i mAreaSize;
	std::vector<sf::IntRect> mSpriteAreas;
};
