#pragma once

#include "SFML/Graphics/Rect.hpp"

class SpriteArea
{
public:
	SpriteArea(const sf::IntRect& area, const sf::Vector2f& origin = {}) noexcept;

	const sf::IntRect& getArea() const noexcept;
	const sf::Vector2f& getOrigin() const noexcept;

private:
	sf::Vector2f mOrigin;
	sf::IntRect mArea;
};
