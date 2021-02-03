#pragma once

#include "SFML/Window/Event.hpp"

#include "TiledMapGrid.hpp"

class TiledMap final : public sf::Drawable
{
public:
	TiledMap();

	void setTileSize(const sf::Vector2f& size);
	void setTileCount(const sf::Vector2i& count);

	void setGridVisible(const bool visible);

	void receiveEvents(const sf::Event& event);

	void build();

	const TiledMapGrid& getGrid() const;

	const sf::Vector2f& getTileSize() const;
	const sf::Vector2i& getTileCount() const;

	bool isGridVisible() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool isContainsPoint(const sf::Vector2f& point) const;

	TiledMapGrid mGrid;
};
