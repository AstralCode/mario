#include "SpritesetRegion.hpp"

SpritesetRegion::SpritesetRegion(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const std::vector<std::vector<SpritesetArea>>& spritesetAreas) noexcept
{
    calculateSpriteAreas(gridSize, gridTileIndex, spritesetAreas);
}

const sf::IntRect& SpritesetRegion::getSprite(const int index) const noexcept
{
    return mSpritesetRegion[index];
}

int SpritesetRegion::getSpriteCount() const noexcept
{
    return static_cast<int>(mSpritesetRegion.size());
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
            auto& spriteArea = spritesetAreas[j][i];

            sf::Vector2i spriteAreaOffset{};
            spriteAreaOffset.x = spriteArea.getGridSize().x * spriteArea.getGridTileIndex().x;
            spriteAreaOffset.y = spriteArea.getGridSize().y * spriteArea.getGridTileIndex().y;

            sf::IntRect sprite{};
            sprite.left = regionOffset.x + spriteAreaOffset.x + spriteArea.getArea().left;
            sprite.top = regionOffset.y + spriteAreaOffset.y + spriteArea.getArea().top;
            sprite.width = spriteArea.getArea().width;
            sprite.height = spriteArea.getArea().height;

            mSpritesetRegion.push_back(sprite);
        }
    }
}
