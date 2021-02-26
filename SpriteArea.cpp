#include "SpriteArea.hpp"

SpriteArea::SpriteArea(const IntArea& area, const FloatPoint& origin) noexcept :
	mArea{area},
	mOrigin{origin}
{

}

const IntArea& SpriteArea::getArea() const noexcept
{
	return mArea;
}

const FloatPoint& SpriteArea::getOrigin() const noexcept
{
	return mOrigin;
}
