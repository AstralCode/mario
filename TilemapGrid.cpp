#include "TilemapGrid.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

TilemapGrid::TilemapGrid() noexcept :
	mTileRowCount{0},
	mTileColumnCount{0},
	mGridColor{sf::Color::White},
	mGridVertexArray{sf::PrimitiveType::Lines},
	mGridVisible{false}
{

}

void TilemapGrid::setTileSize(const FloatSize& size) noexcept
{
	mTileSize = size;
}

void TilemapGrid::setTileCount(const int rowCount, const int columnCount) noexcept
{
	mTileRowCount = rowCount;
	mTileColumnCount = columnCount;
}

void TilemapGrid::setGridColor(const sf::Color& color) noexcept
{
	mGridColor = color;
}

void TilemapGrid::setVisible(const bool visible) noexcept
{
	mGridVisible = visible;
}

void TilemapGrid::build() noexcept
{
	mGridVertexArray.clear();

	buildHorizontalLines();
	buildVerticalLines();
}

bool TilemapGrid::isVisible() const noexcept
{
	return mGridVisible;
}

void TilemapGrid::buildHorizontalLines() noexcept
{
	for (auto row{0}; row < mTileRowCount; ++row)
	{
		FloatPoint left{};
		left.setX(0.0f);
		left.setY(mTileSize.getHeight() * row);

		FloatPoint right{};
		right.setX(mTileSize.getWidth() * mTileColumnCount);
		right.setY(mTileSize.getHeight() * row);

		mGridVertexArray.append(sf::Vertex{left.getVector(), mGridColor});
		mGridVertexArray.append(sf::Vertex{right.getVector(), mGridColor});
	}
}

void TilemapGrid::buildVerticalLines() noexcept
{
	for (auto column{0}; column < mTileColumnCount; ++column)
	{
		FloatPoint top{};
		top.setX(mTileSize.getWidth() * column);
		top.setY(0.0f);

		FloatPoint bottom{};
		bottom.setX(mTileSize.getWidth() * column);
		bottom.setY(mTileSize.getHeight() * mTileRowCount);

		mGridVertexArray.append(sf::Vertex{top.getVector(), mGridColor});
		mGridVertexArray.append(sf::Vertex{bottom.getVector(), mGridColor});
	}
}

void TilemapGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isVisible())
	{
		target.draw(mGridVertexArray, states);
	}
}
