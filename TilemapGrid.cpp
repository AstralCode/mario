#include "TilemapGrid.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

TilemapGrid::TilemapGrid() noexcept :
	mGridColor{sf::Color::White},
	mGridVisible{false}
{
	mTilemapVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
}

void TilemapGrid::setTileSize(const sf::Vector2u& size) noexcept
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

	for (unsigned int y{0u}; y < mTileCount.y; ++y)
	{
		sf::Vector2f horizontalLeft{};
		horizontalLeft.x = 0.0f;
		horizontalLeft.y = static_cast<float>(y * mTileSize.y);

		sf::Vector2f horizontalRight{};
		horizontalRight.x = static_cast<float>(mTileSize.x * mTileCount.x);
		horizontalRight.y = static_cast<float>(y * mTileSize.y);

		mTilemapVertexArray.append(sf::Vertex{horizontalLeft, mGridColor});
		mTilemapVertexArray.append(sf::Vertex{horizontalRight, mGridColor});
	}

	for (unsigned int x{0u}; x < mTileCount.x; ++x)
	{
		sf::Vector2f verticalTop{};
		verticalTop.x = static_cast<float>(x * mTileSize.x);
		verticalTop.y = 0.0f;

		sf::Vector2f verticalBottom{};
		verticalBottom.x = static_cast<float>(x * mTileSize.x);
		verticalBottom.y = static_cast<float>(mTileSize.y * mTileCount.y);

		mTilemapVertexArray.append(sf::Vertex{verticalTop, mGridColor});
		mTilemapVertexArray.append(sf::Vertex{verticalBottom, mGridColor});
	}
}

const sf::Vector2u& TilemapGrid::getTileSize() const noexcept
{
	return mTileSize;
}

const sf::Vector2u& TilemapGrid::getTileCount() const noexcept
{
	return mTileCount;
}

sf::Vector2u TilemapGrid::getTileIndex(const sf::Vector2f& position) const noexcept
{
	return getTileIndex(sf::Vector2i{static_cast<int>(position.x), static_cast<int>(position.y)});
}

sf::Vector2u TilemapGrid::getTileIndex(const sf::Vector2i& mousePosition) const noexcept
{
	sf::Vector2u index{};
	index.x = mousePosition.x / mTileSize.x;
	index.y = mousePosition.y / mTileSize.y;

	return index;
}

sf::Vector2f TilemapGrid::getTilePosition(const sf::Vector2u& index) const noexcept
{
	sf::Vector2f position{};
	position.x = static_cast<float>(mTileSize.x * index.x);
	position.y = static_cast<float>(mTileSize.y * index.y);

	return position;
}

FloatArea TilemapGrid::getTileArea(const sf::Vector2u& index) const noexcept
{
	const auto position = getTilePosition(index);

	sf::FloatRect area{};
	area.left = position.x;
	area.top = position.y;
	area.width = static_cast<float>(mTileSize.x);
	area.height = static_cast<float>(mTileSize.y);

	return area;
}

FloatArea TilemapGrid::getArea() const noexcept
{
	sf::FloatRect rectangle{};
	rectangle.left = 0.0f;
	rectangle.top = 0.0f;
	rectangle.width = static_cast<float>(mTileSize.x * mTileCount.x);
	rectangle.height = static_cast<float>(mTileSize.y * mTileCount.y);

	return rectangle;
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
