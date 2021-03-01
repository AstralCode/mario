#pragma once

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Text.hpp"

#include "TilemapGrid.hpp"
#include "Tilemap.hpp"
#include "Margins.hpp"

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

	void setPosition(const float x, const float y) noexcept;
	void setPosition(const FloatPoint& position) noexcept;
	void setMargins(const float left, const float top, const float right, const float bottom) noexcept;
	void setMargins(const FloatMargins& margins) noexcept;

	void setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept;
	void setTilemapTexture(const sf::Texture& texture) noexcept;

	void setInformationText(const sf::Font& font, const unsigned int characterSize = 12u) noexcept;

	void setBackgroundColor(const sf::Color& color) noexcept;

	void setGridVisible(const bool visible) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void build(const FloatSize& tileSize) noexcept;

	TileIdentifier getIdentifier(const TileIndex& index) const noexcept;

	std::optional<TileAttributeFlags> getAttributes(const TileIdentifier identifier) const noexcept;
	std::optional<TileAttributeFlags> getAttributes(const TileIndex& index) const noexcept;

	TileIndex getTileIndex(const IntPoint& position) const noexcept;
	TileIndex getTileIndex(const FloatPoint& position) const noexcept;

	const FloatSize& getTileSize() const noexcept;

	const int getRowCount() const noexcept;
	const int getColumnCount() const noexcept;

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

	FloatMargins mMargins;

	sf::Transformable mTransform;

	std::unique_ptr<Tilemap> mTilemap;

	const sf::Texture* mTilemapTexture;

	sf::Text mInformationText;

	sf::Color mBackgroundColor;

	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TilemapGrid mGrid;
};
