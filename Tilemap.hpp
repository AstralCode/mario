#pragma once

#include <unordered_map>
#include <optional>

#include "SFML/Window/Event.hpp"

#include "TilemapGrid.hpp"
#include "TileAttributes.hpp"
#include "Flags.hpp"

class Tilemap final : public sf::Drawable
{
public:
	Tilemap();

	void setTilesetTexture(const sf::Texture* tilesetTexture);

	void setTileAttributes(const std::unordered_map<unsigned int, Flags<TileAttributes>>& tileAttributes);
	void setTileIdentifiers(const std::vector<std::vector<unsigned int>>& identifierMap);

	void setBackgroundColor(const sf::Color& color);
	void setGridVisible(const bool visible);

	void receiveEvents(const sf::Event& event);

	void build(const sf::Vector2u& tileSize);

	const TilemapGrid& getGrid() const;

	unsigned int getTileIdentifier(const sf::Vector2u& tileIndex) const;

	const sf::Vector2u& getTileSize() const;
	const sf::Vector2u& getTileCount() const;

	std::optional<Flags<TileAttributes>> getTileAttributes(const sf::Vector2u& tileIndex) const;

	sf::Vector2f getTilePosition(const sf::Vector2u& tileIndex) const;
	sf::Vector2f getTileCenterPosition(const sf::Vector2u& tileIndex) const;

	bool isGridVisible() const;

private:
	void onMouseClick(const sf::Vector2i& position);
	void onMouseMoved(const sf::Vector2i& position);

	sf::Vector2u calculateTextureTilePosition(const unsigned int tileIdentifier, const sf::Vector2u& tileSize) const;
	unsigned int calculateTextureTileIdentifierCount(const sf::Vector2u& tileSize) const;
	sf::Vector2u calculateTileCount() const;

	void setTileSprite(const unsigned int tileIdentifier, const sf::Vector2u& tileIndex);
	void clearTileSprite(const sf::Vector2u& tileIndex);

	sf::Vertex* getTileVerticles(const sf::Vector2u& tileIndex);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool isContainsPoint(const sf::Vector2f& point) const;

	const sf::Texture* mTilesetTexture;

	sf::Color mBackgroundColor;

	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TilemapGrid mGrid;

	std::unordered_map<unsigned int, Flags<TileAttributes>> mTileAttributes;
	std::vector<std::vector<unsigned int>> mTileIdentifiers;
};
