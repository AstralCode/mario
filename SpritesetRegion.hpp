#pragma once

#include <vector>

#include "SpritesetArea.hpp"

class SpritesetRegion final
{
public:
	SpritesetRegion(const IntSize& gridSize, const GridTileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept;

	const IntArea& getSpriteArea(const int number) const noexcept;

	int getSpriteCount() const noexcept;

private:
	void calculateSpriteAreas(const IntSize& gridSize, const GridTileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept;

	std::vector<IntArea> mSpriteAreas;
};
