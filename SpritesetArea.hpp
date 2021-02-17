#pragma once

#include "SpriteArea.hpp"

class SpritesetArea final
{
public:
	SpritesetArea(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const SpriteArea& spriteArea) noexcept;

	const sf::Vector2i& getGridSize() const noexcept;
	const sf::Vector2i& getGridTileIndex() const noexcept;
	const SpriteArea& getSpriteArea() const noexcept;

private:
	sf::Vector2i mGridSize;
	sf::Vector2i mGridTileIndex;
	SpriteArea mSpriteArea;
};
