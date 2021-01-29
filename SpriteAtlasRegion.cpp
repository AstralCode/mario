#include "SpriteAtlasRegion.hpp"

void SpriteAtlasRegion::setOffset(const sf::Vector2i& offset)
{
    mOffset = offset;
}

void SpriteAtlasRegion::setAreaSize(const sf::Vector2i& size)
{
    mAreaSize = size;
}

void SpriteAtlasRegion::setSpriteAreas(const std::vector<sf::IntRect>& areas)
{
    mSpriteAreas = areas;
}

const sf::Vector2i& SpriteAtlasRegion::getOffset() const
{
    return mOffset;
}

const sf::Vector2i& SpriteAtlasRegion::getSpriteSize() const
{
    return mAreaSize;
}

const std::vector<sf::IntRect>& SpriteAtlasRegion::getSpriteAreas() const
{
    return mSpriteAreas;
}
