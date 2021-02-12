#include "SpriteAtlasRegion.hpp"

SpriteAtlasRegion::SpriteAtlasRegion(const sf::Vector2i& spriteSize, const sf::Vector2i& offset, const std::vector<std::vector<sf::IntRect>>& spriteAreas)
{
    calculateSpriteAreas(spriteSize, offset, spriteAreas);
}

const sf::IntRect& SpriteAtlasRegion::getSprite(const int index) const
{
    return mSprites[index];
}

int SpriteAtlasRegion::getSpriteCount() const
{
    return static_cast<int>(mSprites.size());
}

void SpriteAtlasRegion::calculateSpriteAreas(const sf::Vector2i& spriteSize, const sf::Vector2i& offset, const std::vector<std::vector<sf::IntRect>>& spriteAreas)
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

            mSprites.push_back(sprite);
        }
    }
}
