#pragma once

#include "SFML/Graphics/Rect.hpp"

class SpritesetArea final
{
public:
	SpritesetArea(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const sf::IntRect& spriteArea) noexcept;

	const sf::Vector2i& getGridSize() const noexcept;
	const sf::Vector2i& getGridTileIndex() const noexcept;
	const sf::IntRect& getArea() const noexcept;

private:
	sf::Vector2i mGridSize;
	sf::Vector2i mGridTileIndex;
	sf::IntRect mArea;
};
