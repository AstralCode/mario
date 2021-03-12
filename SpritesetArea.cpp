#include "SpritesetArea.hpp"

SpritesetArea::SpritesetArea(const GridSize& gridSize, const GridTileIndex& gridTileIndex, const IntArea& spriteArea) noexcept :
    mGridSize{gridSize},
    mGridTileIndex{gridTileIndex},
    mSpriteArea{spriteArea}
{

}

const GridSize& SpritesetArea::getGridSize() const noexcept
{
    return mGridSize;
}

const GridTileIndex& SpritesetArea::getGridTileIndex() const noexcept
{
    return mGridTileIndex;
}

const SpriteArea& SpritesetArea::getSpriteArea() const noexcept
{
    return mSpriteArea;
}
