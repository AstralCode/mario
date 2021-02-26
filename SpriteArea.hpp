#pragma once

#include "Area.hpp"

class SpriteArea
{
public:
	SpriteArea(const IntArea& area, const FloatPoint& origin = {}) noexcept;

	const IntArea& getArea() const noexcept;
	const FloatPoint& getOrigin() const noexcept;

private:
	IntArea mArea;
	FloatPoint mOrigin;
};
