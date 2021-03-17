#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "Tile.hpp"

class TilemapGrid final : public sf::Drawable
{
public:
	TilemapGrid() noexcept;

	void setTileSize(const FloatSize& size) noexcept;
	void setTileCount(const int rowCount, const int columnCount) noexcept;

	void setGridColor(const sf::Color& color) noexcept;
	void setVisible(const bool visible) noexcept;

	void build() noexcept;

	bool isVisible() const noexcept;

private:
	void buildHorizontalLines() noexcept;
	void buildVerticalLines() noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	FloatSize mTileSize;
	
	int mTileRowCount;
	int mTileColumnCount;

	sf::Color mGridColor;

	sf::VertexArray mGridVertexArray;

	bool mGridVisible;
};
