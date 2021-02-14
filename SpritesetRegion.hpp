#pragma once

#include <vector>

#include "SFML/Graphics/Rect.hpp"

class SpritesetRegion final
{
public:
	SpritesetRegion(const sf::Vector2i& spriteSize, const sf::Vector2i& offset, const std::vector<std::vector<sf::IntRect>>& spriteAreas) noexcept;

	const sf::IntRect& getSprite(const int index) const noexcept;

	int getSpriteCount() const noexcept;

private:
	void calculateSpriteAreas(const sf::Vector2i& spriteSize, const sf::Vector2i& offset, const std::vector<std::vector<sf::IntRect>>& spriteAreas) noexcept;

	std::vector<sf::IntRect> mSpritesetRegion;
};
