#include "SpriteAtlasRegion.hpp"

SpriteAtlasRegion::SpriteAtlasRegion(const sf::Vector2i& offset, const std::vector<std::vector<sf::IntRect>>& areas) :
    mOffset{offset},
    mSpriteAreas{areas}
{

}

void SpriteAtlasRegion::setOffset(const sf::Vector2i& offset)
{
    mOffset = offset;
}

void SpriteAtlasRegion::setSpriteAreas(const std::vector<std::vector<sf::IntRect>>& areas)
{
    mSpriteAreas = areas;
}

const sf::Vector2i& SpriteAtlasRegion::getOffset() const
{
    return mOffset;
}

const std::vector<std::vector<sf::IntRect>>& SpriteAtlasRegion::getSpriteAreas() const
{
    return mSpriteAreas;
}

int SpriteAtlasRegion::getSpriteAreaCount() const
{
    int areaCount{0};

    for (auto& areas : mSpriteAreas)
    {
        areaCount += static_cast<int>(areas.size());
    }

    return areaCount;
}
