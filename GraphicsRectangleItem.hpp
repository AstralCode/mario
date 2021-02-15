#pragma once

#include "SFML/Graphics/RectangleShape.hpp"

#include "GraphicsItem.hpp"

class GraphicsRectangleItem final : public GraphicsItem
{
public:
	void setSize(const sf::Vector2f& size);

	void setFillColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& color);
	void setOutlineThickness(const float thickness);

	const sf::Vector2f& getSize() const;

	sf::FloatRect getBounds() const override;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::RectangleShape mRectangleShape;
};
