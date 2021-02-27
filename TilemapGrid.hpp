#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "Tile.hpp"
#include "Area.hpp"

class TilemapGrid final : public sf::Drawable
{
public:
	TilemapGrid() noexcept;

	void setTileSize(const FloatSize& size) noexcept;
	void setTileCount(const int rowCount, const int columnCount) noexcept;

	void setVisible(const bool visible) noexcept;
	void setGridColor(const sf::Color& color) noexcept;

	void build() noexcept;

	const FloatSize& getTileSize() const noexcept;

	const int getTileRowCount() const noexcept;
	const int getTileColumnCount() const noexcept;

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
	
	int mTileRowCount;
	int mTileColumnCount;

	sf::Color mGridColor;

	sf::VertexArray mTilemapVertexArray;

	bool mGridVisible;
};
