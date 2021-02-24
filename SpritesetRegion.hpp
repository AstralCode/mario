#pragma once

#include <vector>

#include "SpritesetArea.hpp"

class SpritesetRegion final
{
public:
	SpritesetRegion(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept;

	const SpriteArea& getSpriteArea(const int index) const noexcept;

	int getSpriteCount() const noexcept;

private:
	void calculateSpriteAreas(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept;

	std::vector<SpriteArea> mSpriteAreas;
};