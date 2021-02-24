#include "MathCalculator.hpp"

#include <cmath>

float MathCalculator::distance1D(const float x, const float y) noexcept
{
    return std::abs(x - y);
}

float MathCalculator::distance2D(const sf::Vector2f& position1, const sf::Vector2f& position2) noexcept
{
    const auto x = position2.x - position1.x;
    const auto y = position2.y - position1.y;

    return std::sqrt(x * x + y * y);
}
