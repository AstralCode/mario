#include "SpritesetRegion.hpp"

SpritesetRegion::SpritesetRegion(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept
{
    calculateSpriteAreas(gridSize, gridTileIndex, spritesetAreas);
}

const SpriteArea& SpritesetRegion::getSpriteArea(const int index) const noexcept
{
    return mSpriteAreas[index];
}

int SpritesetRegion::getSpriteCount() const noexcept
{
    return static_cast<int>(mSpriteAreas.size());
}

void SpritesetRegion::calculateSpriteAreas(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept
{
    sf::Vector2i regionOffset{};
    regionOffset.x = gridSize.x * gridTileIndex.x;
    regionOffset.y = gridSize.y * gridTileIndex.y;

    for (int j{0}; j < static_cast<int>(spritesetAreas.size()); j++)
    {
        for (int i{0}; i < static_cast<int>(spritesetAreas[j].size()); i++)
        {
            auto& spritesetArea = spritesetAreas[j][i];

            sf::Vector2i spriteAreaOffset{};
            spriteAreaOffset.x = spritesetArea.getGridSize().x * spritesetArea.getGridTileIndex().x;
            spriteAreaOffset.y = spritesetArea.getGridSize().y * spritesetArea.getGridTileIndex().y;

            sf::IntRect spriteArea{};
            spriteArea.left = regionOffset.x + spriteAreaOffset.x + spritesetArea.getSpriteArea().getArea().left;
            spriteArea.top = regionOffset.y + spriteAreaOffset.y + spritesetArea.getSpriteArea().getArea().top;
            spriteArea.width = spritesetArea.getSpriteArea().getArea().width;
            spriteArea.height = spritesetArea.getSpriteArea().getArea().height;

            mSpriteAreas.push_back({spriteArea, spritesetArea.getSpriteArea().getOrigin()});
        }
    }
}
