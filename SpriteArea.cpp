#include "SpriteArea.hpp"

SpriteArea::SpriteArea(const IntArea& area, const OriginPoint& origin) noexcept :
	mArea{area},
	mOrigin{origin}
{

}

const IntArea& SpriteArea::getArea() const noexcept
{
	return mArea;
}

const OriginPoint& SpriteArea::getOrigin() const noexcept
{
	return mOrigin;
}
