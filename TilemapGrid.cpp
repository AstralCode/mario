#include "TilemapGrid.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

TilemapGrid::TilemapGrid() noexcept :
	mTileSize{},
	mGridColor{sf::Color::White},
	mGridVisible{false}
{
	mTilemapVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
}

void TilemapGrid::setTileSize(const FloatSize& size) noexcept
{
	mTileSize = size;
}

void TilemapGrid::setTileCount(const sf::Vector2u& count) noexcept
{
	mTileCount = count;
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

	for (unsigned int y{0}; y < mTileCount.y; ++y)
	{
		FloatPoint horizontalLeft{};
		horizontalLeft.setX(0.0f);
		horizontalLeft.setY(mTileSize.getHeight() * y);

		FloatPoint horizontalRight{};
		horizontalRight.setX(mTileSize.getWidth() * mTileCount.x);
		horizontalRight.setY(mTileSize.getHeight() * y);

		mTilemapVertexArray.append(sf::Vertex(horizontalLeft.getVector(), mGridColor));
		mTilemapVertexArray.append(sf::Vertex(horizontalRight.getVector(), mGridColor));
	}

	for (unsigned int x{0}; x < mTileCount.x; ++x)
	{
		FloatPoint verticalTop{};
		verticalTop.setX(mTileSize.getWidth() * x);
		verticalTop.setY(0.0f);

		FloatPoint verticalBottom{};
		verticalBottom.setX(mTileSize.getWidth() * x);
		verticalBottom.setY(mTileSize.getHeight() * mTileCount.y);

		mTilemapVertexArray.append(sf::Vertex(verticalTop.getVector(), mGridColor));
		mTilemapVertexArray.append(sf::Vertex(verticalBottom.getVector(), mGridColor));
	}
}

const FloatSize& TilemapGrid::getTileSize() const noexcept
{
	return mTileSize;
}

const sf::Vector2u& TilemapGrid::getTileCount() const noexcept
{
	return mTileCount;
}

sf::Vector2u TilemapGrid::getTileIndex(const FloatPoint& position) const noexcept
{
	return getTileIndex(position.cast<int>());
}

sf::Vector2u TilemapGrid::getTileIndex(const IntPoint& position) const noexcept
{
	sf::Vector2u index{};
	index.x = position.getX() / static_cast<unsigned int>(mTileSize.getWidth());
	index.y = position.getY() / static_cast<unsigned int>(mTileSize.getHeight());

	return index;
}

FloatPoint TilemapGrid::getTilePosition(const sf::Vector2u& index) const noexcept
{
	return {mTileSize.getWidth() * index.x, mTileSize.getHeight() * index.y};
}

FloatArea TilemapGrid::getTileArea(const sf::Vector2u& index) const noexcept
{
	const auto position = getTilePosition(index);
	return {position, mTileSize};
}

FloatArea TilemapGrid::getArea() const noexcept
{
	FloatArea area{};
	area.setPosition(0.0f, 0.0f);
	area.setWidth(mTileSize.getWidth() * mTileCount.x);
	area.setHeight(mTileSize.getHeight() * mTileCount.y);

	return area;
}

bool TilemapGrid::isVisible() const noexcept
{
	return mGridVisible;
}

void TilemapGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isVisible())
	{
		target.draw(mTilemapVertexArray, states);
	}
}
