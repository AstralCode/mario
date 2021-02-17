#include "SpriteArea.hpp"

SpriteArea::SpriteArea(const sf::IntRect& area, const sf::Vector2f& origin) noexcept :
	mArea{area},
	mOrigin{origin}
{

}

const sf::IntRect& SpriteArea::getArea() const noexcept
{
	return mArea;
}

const sf::Vector2f& SpriteArea::getOrigin() const noexcept
{
	return mOrigin;
}
