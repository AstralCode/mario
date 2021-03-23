#pragma once

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Text.hpp"

#include "Tilemap.hpp"
#include "TilemapGrid.hpp"

class TilemapView final : public sf::Drawable
{
public:
	TilemapView() noexcept;

	void setPosition(const float x, const float y) noexcept;
	void setPosition(const FloatPoint& position) noexcept;

	void setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept;
	void setTilemapTexture(const sf::Texture& texture) noexcept;

	void setBackgroundColor(const sf::Color& color) noexcept;
	
	void setGridVisible(const bool visible) noexcept;
	void setInformationText(const sf::Font& font, const unsigned int characterSize = 12u) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void build() noexcept;

	Tile getTile(const IntPoint& position) const noexcept;
	Tile getTile(const FloatPoint& position) const noexcept;
	Tile getTile(const Tile::Index& index) const noexcept;

	std::vector<Tile> getTiles(const FloatArea& area) const noexcept;

	FloatPoint getTilePosition(const Tile::Index& index) const noexcept;
	FloatPoint getTileCenterPosition(const Tile::Index& index) const noexcept;

	float getTileWidth() const noexcept;
	float getTileHeight() const noexcept;
	const FloatSize& getTileSize() const noexcept;

	const sf::Text& getText() const noexcept;

	FloatArea getArea() const noexcept;

	const int getRowCount() const noexcept;
	const int getColumnCount() const noexcept;

	bool isGridVisible() const noexcept;

private:
	void setTileSprite(const Tile::Identifier tileIdentifier, const Tile::Index& tileIndex) noexcept;
	void clearTileSprite(const Tile::Index& tileIndex) noexcept;

	void onMouseClick(const IntPoint& position, const sf::Mouse::Button button) noexcept;
	void onMouseMoved(const IntPoint& position) noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2u calculateTextureTilePosition(const Tile::Identifier tileIdentifier) const noexcept;
	unsigned int calculateTextureTileIdentifierCount() const noexcept;
	
	sf::Vertex* getTileSpriteVerticles(const Tile::Index& tileIndex) noexcept;

	bool isContainsPoint(const IntPoint& point) const noexcept;

	sf::Transformable mTransform;

	std::unique_ptr<Tilemap> mTilemap;

	const sf::Texture* mTilemapTexture;

	sf::Color mBackgroundColor;
	sf::Text mInformationText;
	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TilemapGrid mGrid;
};
