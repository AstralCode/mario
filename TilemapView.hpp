#pragma once

#include <map>
#include <optional>

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Text.hpp"

#include "TilemapGrid.hpp"

enum class TileSide
{
	Left,
	Right,
	Top,
	Bottom
};

class TilemapView final : public sf::Drawable
{
public:
	TilemapView() noexcept;

	void setTilesetTexture(const sf::Texture* tilesetTexture) noexcept;

	void setInformationText(const sf::Font& font, const unsigned int characterSize = 12u) noexcept;

	void setTileAttributes(const std::map<TileIdentifier, TileAttributeFlags>& tileAttributes) noexcept;
	void setTileIdentifier(const TileIdentifier identifier, const TileIndex& index) noexcept;
	void setTileIdentifiers(const std::vector<std::vector<TileIdentifier>>& identifiers) noexcept;

	void setBackgroundColor(const sf::Color& color) noexcept;
	void setGridVisible(const bool visible) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void build(const FloatSize& tileSize) noexcept;

	const TilemapGrid& getGrid() const noexcept;

	TileIdentifier getTileIdentifier(const TileIndex& index) const noexcept;

	TileIndex getTileIndex(const IntPoint& position) const noexcept;
	TileIndex getTileIndex(const FloatPoint& position) const noexcept;

	const FloatSize& getTileSize() const noexcept;

	const int getTileRowCount() const noexcept;
	const int getTileColumnCount() const noexcept;

	std::optional<TileAttributeFlags> getTileAttributes(const TileIdentifier identifier) const noexcept;
	std::optional<TileAttributeFlags> getTileAttributes(const TileIndex& index) const noexcept;

	FloatPoint getTilePosition(const TileIndex& index) const noexcept;

	FloatArea getTileArea(const TileIndex& index) const noexcept;

	const sf::Text& getText() const noexcept;

	bool isGridVisible() const noexcept;

private:
	void onMouseClick(const IntPoint& position, const sf::Mouse::Button button) noexcept;
	void onMouseMoved(const IntPoint& position) noexcept;

	sf::Vector2u calculateTextureTilePosition(const TileIdentifier tileIdentifier, const FloatSize& tileSize) const noexcept;
	unsigned int calculateTextureTileIdentifierCount(const FloatSize& tileSize) const noexcept;

	int calculateTileRowCount() const noexcept;
	int calculateTileColumnCount() const noexcept;

	void setTileSprite(const TileIdentifier tileIdentifier, const TileIndex& tileIndex) noexcept;
	void clearTileSprite(const TileIndex& tileIndex) noexcept;

	sf::Vertex* getTileVerticles(const TileIndex& tileIndex) noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool isContainsPoint(const FloatPoint& point) const noexcept;

	const sf::Texture* mTilesetTexture;

	sf::Text mInformationText;

	sf::Color mBackgroundColor;

	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TilemapGrid mGrid;

	std::map<TileIdentifier, TileAttributeFlags> mTileAttributes;
	std::vector<std::vector<TileIdentifier>> mTileIdentifiers;
};