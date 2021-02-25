#pragma once

#include "SFML/Graphics/RectangleShape.hpp"

#include "GraphicsItem.hpp"

class GraphicsRectangleItem final : public GraphicsItem
{
public:
	void setSize(const sf::Vector2f& size) noexcept;

	void setFillColor(const sf::Color& color) noexcept;
	void setOutlineColor(const sf::Color& color) noexcept;
	void setOutlineThickness(const float thickness) noexcept;

	const sf::Vector2f& getSize() const noexcept;

	FloatArea getArea() const noexcept override;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

	sf::RectangleShape mRectangleShape;
};
