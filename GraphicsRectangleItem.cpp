#include "GraphicsRectangleItem.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

void GraphicsRectangleItem::setSize(const sf::Vector2f& size)
{
	mRectangleShape.setSize(size);
}

void GraphicsRectangleItem::setFillColor(const sf::Color& color)
{
	mRectangleShape.setFillColor(color);
}

void GraphicsRectangleItem::setOutlineColor(const sf::Color& color)
{
	mRectangleShape.setOutlineColor(color);
}

void GraphicsRectangleItem::setOutlineThickness(const float thickness)
{
	mRectangleShape.setOutlineThickness(thickness);
}

const sf::Vector2f& GraphicsRectangleItem::getSize() const
{
	return mRectangleShape.getSize();
}

sf::FloatRect GraphicsRectangleItem::getBounds() const
{
	return getGlobalTransform().transformRect(mRectangleShape.getLocalBounds());
}

void GraphicsRectangleItem::drawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mRectangleShape, states);
}
