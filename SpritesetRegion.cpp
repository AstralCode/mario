#include "SpritesetRegion.hpp"

SpritesetRegion::SpritesetRegion(const sf::Vector2i& spriteSize, const sf::Vector2i& offset, const std::vector<std::vector<sf::IntRect>>& spriteAreas) noexcept
{
    calculateSpriteAreas(spriteSize, offset, spriteAreas);
}

const sf::IntRect& SpritesetRegion::getSprite(const int index) const noexcept
{
    return mSpritesetRegion[index];
}

int SpritesetRegion::getSpriteCount() const noexcept
{
    return static_cast<int>(mSpritesetRegion.size());
}

void SpritesetRegion::calculateSpriteAreas(const sf::Vector2i& spriteSize, const sf::Vector2i& offset, const std::vector<std::vector<sf::IntRect>>& spriteAreas) noexcept
{
    for (int j{0}; j < static_cast<int>(spriteAreas.size()); j++)
    {
        for (int i{0}; i < static_cast<int>(spriteAreas[j].size()); i++)
        {
            sf::Vector2i regionOffset{};
            regionOffset.x = offset.x * spriteSize.x;
            regionOffset.y = offset.y * spriteSize.y;

            sf::Vector2i spriteAreaOffset{};
            spriteAreaOffset.x = i * spriteSize.x;
            spriteAreaOffset.y = j * spriteSize.y;

            sf::IntRect sprite{};
            sprite.left = regionOffset.x + spriteAreaOffset.x + spriteAreas[j][i].left;
            sprite.top = regionOffset.y + spriteAreaOffset.y + spriteAreas[j][i].top;
            sprite.width = spriteAreas[j][i].width;
            sprite.height = spriteAreas[j][i].height;

            mSpritesetRegion.push_back(sprite);
        }
    }
}
