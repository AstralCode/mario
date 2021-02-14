#include "SpritesetArea.hpp"

SpritesetArea::SpritesetArea(const sf::Vector2i& gridSize, const sf::Vector2i& gridTileIndex, const sf::IntRect& area) noexcept :
    mGridSize{gridSize},
    mGridTileIndex{gridTileIndex},
    mArea{area}
{

}

const sf::Vector2i& SpritesetArea::getGridSize() const noexcept
{
    return mGridSize;
}

const sf::Vector2i& SpritesetArea::getGridTileIndex() const noexcept
{
    return mGridTileIndex;
}

const sf::IntRect& SpritesetArea::getArea() const noexcept
{
    return mArea;
}
