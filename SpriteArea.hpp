#pragma once

#include "Area.hpp"

class SpriteArea
{
public:
	SpriteArea(const IntArea& area, const sf::Vector2f& origin = {}) noexcept;

	const IntArea& getArea() const noexcept;
	const sf::Vector2f& getOrigin() const noexcept;

private:
	IntArea mArea;
	sf::Vector2f mOrigin;
};
