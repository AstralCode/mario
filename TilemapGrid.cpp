#include "TilemapGrid.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

TilemapGrid::TilemapGrid() noexcept :
	mTileSize{},
	mRowCount{0},
	mColumnCount{0},
	mGridColor{sf::Color::White},
	mGridVisible{false}
{
	mTilemapVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
}

void TilemapGrid::setTileSize(const float x, const float y) noexcept
{
	mTileSize.set(x, y);
}

void TilemapGrid::setTileSize(const FloatSize& size) noexcept
{
	mTileSize = size;
}

void TilemapGrid::setTileCount(const int rowCount, const int columnCount) noexcept
{
	mRowCount = rowCount;
	mColumnCount = columnCount;
}

void TilemapGrid::setVisible(const bool visible) noexcept
{
	mGridVisible = visible;
}

void TilemapGrid::setGridColor(const sf::Color& color) noexcept
{
	mGridColor = color;
}

void TilemapGrid::build() noexcept
{
	mTilemapVertexArray.clear();

	buildHorizontalLines();
	buildVerticalLines();
}

const FloatSize& TilemapGrid::getTileSize() const noexcept
{
	return mTileSize;
}

const int TilemapGrid::getRowCount() const noexcept
{
	return mRowCount;
}

const int TilemapGrid::getColumnCount() const noexcept
{
	return mColumnCount;
}

TileIndex TilemapGrid::getTileIndex(const FloatPoint& position) const noexcept
{
	return getTileIndex(position.cast<int>());
}

TileIndex TilemapGrid::getTileIndex(const IntPoint& position) const noexcept
{
	TileIndex index{};
	index.row = position.getX() / static_cast<unsigned int>(mTileSize.getWidth());
	index.column = position.getY() / static_cast<unsigned int>(mTileSize.getHeight());

	return index;
}

FloatPoint TilemapGrid::getTilePosition(const TileIndex& index) const noexcept
{
	return {mTileSize.getWidth() * index.row, mTileSize.getHeight() * index.column};
}

FloatArea TilemapGrid::getTileArea(const TileIndex& index) const noexcept
{
	const auto position = getTilePosition(index);
	return {position, mTileSize};
}

FloatArea TilemapGrid::getArea() const noexcept
{
	FloatArea area{};
	area.setPosition(0.0f, 0.0f);
	area.setWidth(mTileSize.getWidth() * mRowCount);
	area.setHeight(mTileSize.getHeight() * mColumnCount);

	return area;
}

bool TilemapGrid::isVisible() const noexcept
{
	return mGridVisible;
}

void TilemapGrid::buildHorizontalLines() noexcept
{
	for (auto columnIndex{0}; columnIndex < mColumnCount; ++columnIndex)
	{
		FloatPoint horizontalLeft{};
		horizontalLeft.setX(0.0f);
		horizontalLeft.setY(mTileSize.getHeight() * columnIndex);

		FloatPoint horizontalRight{};
		horizontalRight.setX(mTileSize.getWidth() * mRowCount);
		horizontalRight.setY(mTileSize.getHeight() * columnIndex);

		mTilemapVertexArray.append(sf::Vertex(horizontalLeft.getVector(), mGridColor));
		mTilemapVertexArray.append(sf::Vertex(horizontalRight.getVector(), mGridColor));
	}
}

void TilemapGrid::buildVerticalLines() noexcept
{
	for (auto rowIndex{0}; rowIndex < mRowCount; ++rowIndex)
	{
		FloatPoint verticalTop{};
		verticalTop.setX(mTileSize.getWidth() * rowIndex);
		verticalTop.setY(0.0f);

		FloatPoint verticalBottom{};
		verticalBottom.setX(mTileSize.getWidth() * rowIndex);
		verticalBottom.setY(mTileSize.getHeight() * mColumnCount);

		mTilemapVertexArray.append(sf::Vertex(verticalTop.getVector(), mGridColor));
		mTilemapVertexArray.append(sf::Vertex(verticalBottom.getVector(), mGridColor));
	}
}

void TilemapGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isVisible())
	{
		target.draw(mTilemapVertexArray, states);
	}
}
