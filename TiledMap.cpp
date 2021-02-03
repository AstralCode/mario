#include "TiledMap.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

TiledMap::TiledMap()
{

}

void TiledMap::setTileSize(const sf::Vector2f& size)
{
	mGrid.setTileSize(size);
}

void TiledMap::setTileCount(const sf::Vector2i& count)
{
	mGrid.setTileCount(count);
}

void TiledMap::setGridVisible(const bool visible)
{
	mGrid.setVisible(visible);
}

void TiledMap::receiveEvents(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		if (isContainsPoint({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)}))
		{

		}
		break;
	}

	case sf::Event::MouseMoved:
	{
		if (isContainsPoint({static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)}))
		{

		}
		break;
	}

	default:
		break;
	}
}

void TiledMap::build()
{
	mGrid.build();
}

const TiledMapGrid& TiledMap::getGrid() const
{
	return mGrid;
}

const sf::Vector2f& TiledMap::getTileSize() const
{
	return mGrid.getTileSize();
}

const sf::Vector2i& TiledMap::getTileCount() const
{
	return mGrid.getTileCount();
}

bool TiledMap::isGridVisible() const
{
	return mGrid.isVisible();
}

void TiledMap::draw(sf::RenderTarget&, sf::RenderStates) const
{

}

bool TiledMap::isContainsPoint(const sf::Vector2f& point) const
{
	return mGrid.getBounds().contains(point);
}
