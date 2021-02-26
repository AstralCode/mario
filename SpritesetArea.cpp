#include "SpritesetArea.hpp"

SpritesetArea::SpritesetArea(const IntSize& gridSize, const sf::Vector2i& gridTileIndex, const SpriteArea& spriteArea) noexcept :
    mGridSize{gridSize},
    mGridTileIndex{gridTileIndex},
    mSpriteArea{spriteArea}
{

}

const IntSize& SpritesetArea::getGridSize() const noexcept
{
    return mGridSize;
}

const sf::Vector2i& SpritesetArea::getGridTileIndex() const noexcept
{
    return mGridTileIndex;
}

const SpriteArea& SpritesetArea::getSpriteArea() const noexcept
{
    return mSpriteArea;
}
