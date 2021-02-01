#include "SpriteAtlasRegion.hpp"

SpriteAtlasRegion::SpriteAtlasRegion(const sf::Vector2i& offset, const sf::Vector2i& spriteSize, const std::vector<std::vector<sf::IntRect>>& areas)
{
    initializeSpriteAreas(offset, spriteSize, areas);
}

const sf::IntRect& SpriteAtlasRegion::getSprite(const int index) const
{
    return mSpriteAreas[index];
}

int SpriteAtlasRegion::getSpriteCount() const
{
    return static_cast<int>(mSpriteAreas.size());
}

void SpriteAtlasRegion::initializeSpriteAreas(const sf::Vector2i& offset, const sf::Vector2i& spriteSize, const std::vector<std::vector<sf::IntRect>>& areas)
{
    for (int j{0}; j < static_cast<int>(areas.size()); j++)
    {
        for (int i{0}; i < static_cast<int>(areas[j].size()); i++)
        {
            sf::IntRect spriteArea{};
            spriteArea.left = (offset.x * spriteSize.x) + (i * spriteSize.x) + areas[j][i].left;
            spriteArea.top = (offset.y * spriteSize.y) + (j * spriteSize.y) + areas[j][i].top;
            spriteArea.width = areas[j][i].width;
            spriteArea.height = areas[j][i].height;

            mSpriteAreas.push_back(spriteArea);
        }
    }
}
