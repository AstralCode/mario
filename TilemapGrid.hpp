#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "Area.hpp"

class TilemapGrid final : public sf::Drawable
{
public:
	TilemapGrid() noexcept;

	void setTileSize(const sf::Vector2u& size) noexcept;
	void setTileCount(const sf::Vector2u& count) noexcept;

	void setVisible(const bool visible) noexcept;
	void setGridColor(const sf::Color& color) noexcept;

	void build() noexcept;

	const sf::Vector2u& getTileSize() const noexcept;
	const sf::Vector2u& getTileCount() const noexcept;

	sf::Vector2u getTileIndex(const FloatPoint& position) const noexcept;
	sf::Vector2u getTileIndex(const IntPoint& position) const noexcept;
	sf::Vector2f getTilePosition(const sf::Vector2u& index) const noexcept;

	FloatArea getTileArea(const sf::Vector2u& index) const noexcept;
	FloatArea getArea() const noexcept;

	bool isVisible() const noexcept;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2u mTileSize;
	sf::Vector2u mTileCount;

	sf::Color mGridColor;

	sf::VertexArray mTilemapVertexArray;

	bool mGridVisible;
};
