#pragma once

#include "SFML/Window/Event.hpp"

#include "TiledMapGrid.hpp"

class TiledMap final : public sf::Drawable
{
public:
	TiledMap();

	void setTileset(const sf::Texture* tileset);
	void setTileIdentifierMap(const std::vector<std::vector<unsigned int>>& identifierMap);

	void setBackgroundColor(const sf::Color& color);
	void setGridVisible(const bool visible);

	void receiveEvents(const sf::Event& event);

	void build(const sf::Vector2u& tileSize);

	const TiledMapGrid& getGrid() const;

	const sf::Vector2u& getTileSize() const;
	const sf::Vector2u& getTileCount() const;

	sf::Vector2f getTilePosition(const sf::Vector2u& tileIndex) const;
	sf::Vector2f getTileCenterPosition(const sf::Vector2u& tileIndex) const;

	bool isGridVisible() const;

private:
	sf::Vector2u calculateTextureTilePosition(const unsigned int tileIdentifier, const sf::Vector2u& tileSize) const;
	unsigned int calculateTextureTileIdentifierCount(const sf::Vector2u& tileSize) const;
	sf::Vector2u calculateTileCount() const;

	void setTileSprite(const unsigned int tileIdentifier, const sf::Vector2u& tileIndex);
	void clearTileSprite(const sf::Vector2u& tileIndex);

	sf::Vertex* getTileVerticles(const sf::Vector2u& tileIndex);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool isContainsPoint(const sf::Vector2f& point) const;

	const sf::Texture* mTileset;

	sf::Color mBackgroundColor;

	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TiledMapGrid mGrid;

	std::vector<std::vector<unsigned int>> mTileIdentifierMap;
};
