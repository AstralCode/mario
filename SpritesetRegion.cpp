#include "SpritesetRegion.hpp"

SpritesetRegion::SpritesetRegion(const IntSize& gridSize, const TileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept
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

void SpritesetRegion::calculateSpriteAreas(const IntSize& gridSize, const TileIndex& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept
{
    IntPoint regionOffset{};
    regionOffset.setX(gridSize.getWidth() * gridTileIndex.row);
    regionOffset.setY(gridSize.getHeight() * gridTileIndex.column);

    for (int j{0}; j < static_cast<int>(spritesetAreas.size()); j++)
    {
        for (int i{0}; i < static_cast<int>(spritesetAreas[j].size()); i++)
        {
            auto& spritesetArea = spritesetAreas[j][i];

            IntPoint spriteAreaOffset{};
            spriteAreaOffset.setX(spritesetArea.getGridSize().getWidth() * spritesetArea.getGridTileIndex().row);
            spriteAreaOffset.setY(spritesetArea.getGridSize().getHeight() * spritesetArea.getGridTileIndex().column);

            IntArea spriteArea{};
            spriteArea.setX(regionOffset.getX() + spriteAreaOffset.getX() + spritesetArea.getSpriteArea().getArea().getX());
            spriteArea.setY(regionOffset.getY() + spriteAreaOffset.getY() + spritesetArea.getSpriteArea().getArea().getY());
            spriteArea.setWidth(spritesetArea.getSpriteArea().getArea().getWidth());
            spriteArea.setHeight(spritesetArea.getSpriteArea().getArea().getHeight());

            mSpriteAreas.push_back(SpriteArea{spriteArea, spritesetArea.getSpriteArea().getOrigin()});
        }
    }
}
