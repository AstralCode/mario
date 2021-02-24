#pragma once

#include <map>
#include <optional>

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Text.hpp"

#include "TilemapGrid.hpp"
#include "TileAttributes.hpp"
#include "Flags.hpp"

class Tilemap final : public sf::Drawable
{
public:
	Tilemap();

	void setTilesetTexture(const sf::Texture* tilesetTexture);

	void setInformationText(const sf::Font& font, const unsigned int characterSize = 12u);

	void setTileAttributes(const std::map<unsigned int, TileAttributeFlags>& tileAttributes);
	void setTileIdentifier(const unsigned int identifier, const sf::Vector2u& tileIndex);
	void setTileIdentifiers(const std::vector<std::vector<unsigned int>>& identifiers);

	void setBackgroundColor(const sf::Color& color);
	void setGridVisible(const bool visible);

	void receiveEvents(const sf::Event& event);

	void build(const sf::Vector2u& tileSize);

	const TilemapGrid& getGrid() const;

	unsigned int getTileIdentifier(const sf::Vector2u& tileIndex) const;
	sf::Vector2u getTileIndex(const sf::Vector2f& position) const;

	const sf::Vector2u& getTileSize() const;
	const sf::Vector2u& getTileCount() const;

	std::optional<TileAttributeFlags> getTileAttributes(const unsigned int identifier) const;
	std::optional<TileAttributeFlags> getTileAttributes(const sf::Vector2u& tileIndex) const;

	sf::Vector2f getTilePosition(const sf::Vector2u& tileIndex) const;
	sf::Vector2f getTileTopLeftPosition(const sf::Vector2u& tileIndex) const;
	sf::Vector2f getTileTopRightPosition(const sf::Vector2u& tileIndex) const;
	sf::Vector2f getTileCenterPosition(const sf::Vector2u& tileIndex) const;

	sf::FloatRect getTileArea(const sf::Vector2u& tileIndex) const;

	const sf::Text& getText() const;

	bool isGridVisible() const;

private:
	void onMouseClick(const sf::Vector2i& position, const sf::Mouse::Button button);
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

	sf::Text mInformationText;

	sf::Color mBackgroundColor;

	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TilemapGrid mGrid;

	std::map<unsigned int, TileAttributeFlags> mTileAttributes;
	std::vector<std::vector<unsigned int>> mTileIdentifiers;
};
