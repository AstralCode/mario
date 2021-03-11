#pragma once

#include "Area.hpp"
#include "Tile.hpp"

using GridSize = IntSize;
using GridTileIndex = TileIndex;

class SpritesetArea final
{
public:
	SpritesetArea(const GridSize& gridSize, const GridTileIndex& gridTileIndex, const IntArea& spriteArea) noexcept;

	const GridSize& getGridSize() const noexcept;
	const GridTileIndex& getGridTileIndex() const noexcept;
	const IntArea& getSpriteArea() const noexcept;

private:
	GridSize mGridSize;
	GridTileIndex mGridTileIndex;
	IntArea mSpriteArea;
};
