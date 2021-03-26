#pragma once

#include "Tile.hpp"

using GridSize = IntSize;
using GridTileIndex = TileIndex;
using SpriteArea = IntArea;

class SpritesetArea final
{
public:
	SpritesetArea(const GridSize& gridSize, const GridTileIndex& gridTileIndex, const SpriteArea& spriteArea) noexcept;

	const GridSize& getGridSize() const noexcept;
	const GridTileIndex& getGridTileIndex() const noexcept;
	const SpriteArea& getSpriteArea() const noexcept;

private:
	GridSize mGridSize;
	GridTileIndex mGridTileIndex;
	SpriteArea mSpriteArea;
};
