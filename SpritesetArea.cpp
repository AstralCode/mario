#include "SpritesetArea.hpp"

SpritesetArea::SpritesetArea(const IntSize& gridSize, const TileIndex& gridTileIndex, const SpriteArea& spriteArea) noexcept :
    mGridSize{gridSize},
    mGridTileIndex{gridTileIndex},
    mSpriteArea{spriteArea}
{

}

const IntSize& SpritesetArea::getGridSize() const noexcept
{
    return mGridSize;
}

const TileIndex& SpritesetArea::getGridTileIndex() const noexcept
{
    return mGridTileIndex;
}

const SpriteArea& SpritesetArea::getSpriteArea() const noexcept
{
    return mSpriteArea;
}
