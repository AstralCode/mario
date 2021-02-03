#include "TiledMapGrid.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

TiledMapGrid::TiledMapGrid() :
	mGridColor{sf::Color::White},
	mGridVisible{false}
{
	mTiledMapVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
}

void TiledMapGrid::setTileSize(const sf::Vector2f& size)
{
	mTileSize = size;
}

void TiledMapGrid::setTileCount(const sf::Vector2i& count)
{
	mTileCount = count;
}

void TiledMapGrid::setVisible(const bool visible)
{
	mGridVisible = visible;
}

void TiledMapGrid::setGridColor(const sf::Color& color)
{
	mGridColor = color;
}

void TiledMapGrid::build()
{
	mTiledMapVertexArray.clear();

	for (int y{0}; y < mTileCount.y; ++y)
	{
		sf::Vector2f horizontalLeft{};
		horizontalLeft.x = 0.0f;
		horizontalLeft.y = y * mTileSize.y;

		sf::Vector2f horizontalRight{};
		horizontalRight.x = mTileSize.x * mTileCount.x;
		horizontalRight.y = y * mTileSize.y;

		mTiledMapVertexArray.append(sf::Vertex{horizontalLeft, mGridColor});
		mTiledMapVertexArray.append(sf::Vertex{horizontalRight, mGridColor});
	}

	for (int x{0}; x < mTileCount.x; ++x)
	{
		sf::Vector2f verticalTop{};
		verticalTop.x = x * mTileSize.x;
		verticalTop.y = 0.0f;

		sf::Vector2f verticalBottom{};
		verticalBottom.x = x * mTileSize.x;
		verticalBottom.y = mTileSize.y * mTileCount.y;

		mTiledMapVertexArray.append(sf::Vertex{verticalTop, mGridColor});
		mTiledMapVertexArray.append(sf::Vertex{verticalBottom, mGridColor});
	}
}

const sf::Vector2f& TiledMapGrid::getTileSize() const
{
	return mTileSize;
}

const sf::Vector2i& TiledMapGrid::getTileCount() const
{
	return mTileCount;
}

sf::Vector2i TiledMapGrid::getTileIndex(const sf::Vector2i& mousePosition) const
{
	sf::Vector2i index{};
	index.x = mousePosition.x / mTileSize.x;
	index.y = mousePosition.y / mTileSize.y;

	return index;
}

sf::Vector2f TiledMapGrid::getTilePosition(const sf::Vector2i& index) const
{
	sf::Vector2f position{};
	position.x = mTileSize.x * index.x;
	position.y = mTileSize.y * index.y;

	return position;
}

sf::FloatRect TiledMapGrid::getBounds() const
{
	sf::FloatRect bounds{};
	bounds.left = 0.0f;
	bounds.top = 0.0f;
	bounds.width = mTileSize.x * mTileCount.x;
	bounds.height = mTileSize.y * mTileCount.y;

	return bounds;
}

bool TiledMapGrid::isVisible() const
{
	return mGridVisible;
}

void TiledMapGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isVisible())
	{
		target.draw(mTiledMapVertexArray, states);
	}
}
