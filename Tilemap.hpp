#pragma once

#include <map>
#include <optional>

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Text.hpp"

#include "TilemapGrid.hpp"
#include "TileAttributes.hpp"
#include "Flags.hpp"

enum class TileSide
{
	Left,
	Right,
	Top,
	Bottom
};

class Tilemap final : public sf::Drawable
{
public:
	Tilemap() noexcept;

	void setTilesetTexture(const sf::Texture* tilesetTexture) noexcept;

	void setInformationText(const sf::Font& font, const unsigned int characterSize = 12u) noexcept;

	void setTileAttributes(const std::map<unsigned int, TileAttributeFlags>& tileAttributes) noexcept;
	void setTileIdentifier(const unsigned int identifier, const sf::Vector2u& index) noexcept;
	void setTileIdentifiers(const std::vector<std::vector<unsigned int>>& identifiers) noexcept;

	void setBackgroundColor(const sf::Color& color) noexcept;
	void setGridVisible(const bool visible) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void build(const FloatSize& tileSize) noexcept;

	TileSide getTileSide(const FloatArea& area, const sf::Vector2u& tileIndex) const noexcept;

	const TilemapGrid& getGrid() const noexcept;

	unsigned int getTileIdentifier(const sf::Vector2u& index) const noexcept;

	sf::Vector2u getTileIndex(const IntPoint& position) const noexcept;
	sf::Vector2u getTileIndex(const FloatPoint& position) const noexcept;

	const FloatSize& getTileSize() const noexcept;
	const sf::Vector2u& getTileCount() const noexcept;

	std::optional<TileAttributeFlags> getTileAttributes(const unsigned int identifier) const noexcept;
	std::optional<TileAttributeFlags> getTileAttributes(const sf::Vector2u& index) const noexcept;

	FloatPoint getTilePosition(const sf::Vector2u& index) const noexcept;

	FloatArea getTileArea(const sf::Vector2u& index) const noexcept;

	const sf::Text& getText() const noexcept;

	bool isGridVisible() const noexcept;

private:
	void onMouseClick(const IntPoint& position, const sf::Mouse::Button button) noexcept;
	void onMouseMoved(const IntPoint& position) noexcept;

	sf::Vector2u calculateTextureTilePosition(const unsigned int tileIdentifier, const FloatSize& tileSize) const noexcept;
	unsigned int calculateTextureTileIdentifierCount(const FloatSize& tileSize) const noexcept;
	sf::Vector2u calculateTileCount() const noexcept;

	void setTileSprite(const unsigned int tileIdentifier, const sf::Vector2u& tileIndex) noexcept;
	void clearTileSprite(const sf::Vector2u& tileIndex) noexcept;

	sf::Vertex* getTileVerticles(const sf::Vector2u& tileIndex) noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool isContainsPoint(const sf::Vector2f& point) const noexcept;

	const sf::Texture* mTilesetTexture;

	sf::Text mInformationText;

	sf::Color mBackgroundColor;

	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TilemapGrid mGrid;

	std::map<unsigned int, TileAttributeFlags> mTileAttributes;
	std::vector<std::vector<unsigned int>> mTileIdentifiers;
};
