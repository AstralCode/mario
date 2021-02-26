#pragma once

#include "SpriteArea.hpp"

class SpritesetArea final
{
public:
	SpritesetArea(const IntSize& gridSize, const sf::Vector2i& gridTileIndex, const SpriteArea& spriteArea) noexcept;

	const IntSize& getGridSize() const noexcept;
	const sf::Vector2i& getGridTileIndex() const noexcept;
	const SpriteArea& getSpriteArea() const noexcept;

private:
	IntSize mGridSize;
	sf::Vector2i mGridTileIndex;
	SpriteArea mSpriteArea;
};
