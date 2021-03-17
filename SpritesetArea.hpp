#pragma once

#include "Area.hpp"
#include "Tile.hpp"

using GridSize = IntSize;
using GridTileIndex = Tile::Index;
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
