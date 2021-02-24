#pragma once

#include "SFML/Graphics/Rect.hpp"

class MathCalculator final
{
public:
	MathCalculator() = delete;

	static float distance1D(const float x, const float y) noexcept;
	static float distance2D(const sf::Vector2f& position1, const sf::Vector2f& position2) noexcept;
};
