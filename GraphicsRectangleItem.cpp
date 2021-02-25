#include "GraphicsRectangleItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

void GraphicsRectangleItem::setSize(const sf::Vector2f& size) noexcept
{
	mRectangleShape.setSize(size);
}

void GraphicsRectangleItem::setFillColor(const sf::Color& color) noexcept
{
	mRectangleShape.setFillColor(color);
}

void GraphicsRectangleItem::setOutlineColor(const sf::Color& color) noexcept
{
	mRectangleShape.setOutlineColor(color);
}

void GraphicsRectangleItem::setOutlineThickness(const float thickness) noexcept
{
	mRectangleShape.setOutlineThickness(thickness);
}

const sf::Vector2f& GraphicsRectangleItem::getSize() const noexcept
{
	return mRectangleShape.getSize();
}

FloatArea GraphicsRectangleItem::getArea() const noexcept
{
	return getGlobalTransform().transformRect(mRectangleShape.getLocalBounds());
}

void GraphicsRectangleItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
	target.draw(mRectangleShape, states);
}
