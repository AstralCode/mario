#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "Tile.hpp"
#include "Area.hpp"

class TilemapGrid final : public sf::Drawable
{
public:
	TilemapGrid() noexcept;

	void setTileSize(const float x, const float y) noexcept;
	void setTileSize(const FloatSize& size) noexcept;
	void setTileCount(const int rowCount, const int columnCount) noexcept;

	void setVisible(const bool visible) noexcept;
	void setGridColor(const sf::Color& color) noexcept;

	void build() noexcept;

	const FloatSize& getTileSize() const noexcept;

	const int getRowCount() const noexcept;
	const int getColumnCount() const noexcept;

	TileIndex getTileIndex(const FloatPoint& position) const noexcept;
	TileIndex getTileIndex(const IntPoint& position) const noexcept;

	FloatPoint getTilePosition(const TileIndex& index) const noexcept;

	FloatArea getTileArea(const TileIndex& index) const noexcept;
	FloatArea getArea() const noexcept;

	bool isVisible() const noexcept;

private:
	void buildHorizontalLines() noexcept;
	void buildVerticalLines() noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	FloatSize mTileSize;
	
	int mRowCount;
	int mColumnCount;

	sf::Color mGridColor;

	sf::VertexArray mTilemapVertexArray;

	bool mGridVisible;
};
