#include "SpriteArea.hpp"

SpriteArea::SpriteArea(const IntArea& area, const sf::Vector2f& origin) noexcept :
	mArea{area},
	mOrigin{origin}
{

}

const IntArea& SpriteArea::getArea() const noexcept
{
	return mArea;
}

const sf::Vector2f& SpriteArea::getOrigin() const noexcept
{
	return mOrigin;
}
