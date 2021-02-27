#pragma once

#include "SpriteArea.hpp"
#include "Tile.hpp"

class SpritesetArea final
{
public:
	SpritesetArea(const IntSize& gridSize, const TileIndex& gridTileIndex, const SpriteArea& spriteArea) noexcept;

	const IntSize& getGridSize() const noexcept;
	const TileIndex& getGridTileIndex() const noexcept;
	const SpriteArea& getSpriteArea() const noexcept;

private:
	IntSize mGridSize;
	TileIndex mGridTileIndex;
	SpriteArea mSpriteArea;
};
