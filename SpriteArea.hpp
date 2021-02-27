#pragma once

#include "Area.hpp"

using OriginPoint = FloatPoint;

class SpriteArea
{
public:
	SpriteArea(const IntArea& area, const OriginPoint& origin = {}) noexcept;

	const IntArea& getArea() const noexcept;
	const OriginPoint& getOrigin() const noexcept;

private:
	IntArea mArea;
	OriginPoint mOrigin;
};
