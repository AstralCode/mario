#pragma once

#include "SFML/Graphics/RectangleShape.hpp"

#include "GraphicsItem.hpp"

class RectangleShape final : public GraphicsItem
{
public:
	void setSize(const FloatSize& size) noexcept;

	void setFillColor(const sf::Color& color) noexcept;
	void setOutlineColor(const sf::Color& color) noexcept;
	void setOutlineThickness(const float thickness) noexcept;

	FloatSize getSize() const noexcept;

	FloatArea getArea() const noexcept override;

private:
	void drawSelf(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

	sf::RectangleShape mRectangleShape;
};
