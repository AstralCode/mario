#include "SpritesetRegion.hpp"

SpritesetRegion::SpritesetRegion(const IntSize& gridSize, const GridTileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept
{
    calculateSpriteAreas(gridSize, gridTileIndex, spritesetAreas);
}

const SpriteArea& SpritesetRegion::getSpriteArea(const int number) const noexcept
{
    return mSpriteAreas[number];
}

int SpritesetRegion::getSpriteCount() const noexcept
{
    return static_cast<int>(mSpriteAreas.size());
}

void SpritesetRegion::calculateSpriteAreas(const IntSize& gridSize, const GridTileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept
{
    IntPoint regionOffset{};
    regionOffset.setX(gridSize.getWidth() * gridTileIndex.getRow());
    regionOffset.setY(gridSize.getHeight() * gridTileIndex.getColumn());

    for (std::size_t j{0u}; j < spritesetAreas.size(); j++)
    {
        for (std::size_t i{0u}; i < spritesetAreas[j].size(); i++)
        {
            auto& spritesetArea = spritesetAreas[j][i];

            IntArea spriteAreaOffset{};
            spriteAreaOffset.setX(spritesetArea.getGridSize().getWidth() * spritesetArea.getGridTileIndex().getRow());
            spriteAreaOffset.setY(spritesetArea.getGridSize().getHeight() * spritesetArea.getGridTileIndex().getColumn());

            SpriteArea spriteArea{};
            spriteArea.setX(regionOffset.getX() + spriteAreaOffset.getX() + spritesetArea.getSpriteArea().getX());
            spriteArea.setY(regionOffset.getY() + spriteAreaOffset.getY() + spritesetArea.getSpriteArea().getY());
            spriteArea.setWidth(spritesetArea.getSpriteArea().getWidth());
            spriteArea.setHeight(spritesetArea.getSpriteArea().getHeight());

            mSpriteAreas.push_back(spriteArea);
        }
    }
}
