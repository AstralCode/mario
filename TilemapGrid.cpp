#include "TilemapGrid.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

TilemapGrid::TilemapGrid() :
	mGridColor{sf::Color::White},
	mGridVisible{false}
{
	mTilemapVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
}

void TilemapGrid::setTileSize(const sf::Vector2u& size)
{
	mTileSize = size;
}

void TilemapGrid::setTileCount(const sf::Vector2u& count)
{
	mTileCount = count;
}

void TilemapGrid::setVisible(const bool visible)
{
	mGridVisible = visible;
}

void TilemapGrid::setGridColor(const sf::Color& color)
{
	mGridColor = color;
}

void TilemapGrid::build()
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

const sf::Vector2u& TilemapGrid::getTileSize() const
{
	return mTileSize;
}

const sf::Vector2u& TilemapGrid::getTileCount() const
{
	return mTileCount;
}

sf::Vector2u TilemapGrid::getTileIndex(const sf::Vector2f& position) const
{
	return getTileIndex(sf::Vector2i{static_cast<int>(position.x), static_cast<int>(position.y)});
}

sf::Vector2u TilemapGrid::getTileIndex(const sf::Vector2i& mousePosition) const
{
	sf::Vector2u index{};
	index.x = mousePosition.x / mTileSize.x;
	index.y = mousePosition.y / mTileSize.y;

	return index;
}

sf::Vector2f TilemapGrid::getTilePosition(const sf::Vector2u& index) const
{
	sf::Vector2f position{};
	position.x = static_cast<float>(mTileSize.x * index.x);
	position.y = static_cast<float>(mTileSize.y * index.y);

	return position;
}

sf::FloatRect TilemapGrid::getTileArea(const sf::Vector2u& index) const
{
	sf::FloatRect area{};

	const auto position = getTilePosition(index);

	area.left = position.x;
	area.top = position.y;
	area.width = mTileSize.x;
	area.height = mTileSize.y;

	return area;
}

sf::FloatRect TilemapGrid::getBounds() const
{
	sf::FloatRect bounds{};
	bounds.left = 0.0f;
	bounds.top = 0.0f;
	bounds.width = static_cast<float>(mTileSize.x * mTileCount.x);
	bounds.height = static_cast<float>(mTileSize.y * mTileCount.y);

	return bounds;
}

bool TilemapGrid::isVisible() const
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
