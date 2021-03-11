#include "RectangleShape.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

void RectangleShape::setSize(const FloatSize& size) noexcept
{
	mRectangleShape.setSize({size.getWidth(), size.getHeight()});
}

void RectangleShape::setFillColor(const sf::Color& color) noexcept
{
	mRectangleShape.setFillColor(color);
}

void RectangleShape::setOutlineColor(const sf::Color& color) noexcept
{
	mRectangleShape.setOutlineColor(color);
}

void RectangleShape::setOutlineThickness(const float thickness) noexcept
{
	mRectangleShape.setOutlineThickness(thickness);
}

FloatSize RectangleShape::getSize() const noexcept
{
	return mRectangleShape.getSize();
}

void RectangleShape::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(mRectangleShape, states);
}

FloatArea RectangleShape::getLocalArea() const noexcept
{
	return mRectangleShape.getLocalBounds();
}
