#pragma once

#include <vector>

#include "SpritesetArea.hpp"

class SpritesetRegion final
{
public:
	SpritesetRegion() noexcept = default;
	SpritesetRegion(const IntSize& gridSize, const GridTileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept;

	const SpriteArea& getSpriteArea(const int number) const noexcept;

	int getSpriteCount() const noexcept;

private:
	void calculateSpriteAreas(const IntSize& gridSize, const GridTileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept;

	std::vector<IntArea> mSpriteAreas;
};
