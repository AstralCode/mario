#pragma once

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Window/Event.hpp"

#include <functional>

#include "Tilemap.hpp"
#include "TilemapGrid.hpp"

class TilemapView final : public sf::Drawable
{
public:
	using OnMouseClickDelegate = std::function<void(const IntPoint&, const sf::Mouse::Button)>;
	using OnMouseMoveDelegate = std::function<void(const IntPoint&)>;

	TilemapView() noexcept;

	void setPosition(const float x, const float y) noexcept;
	void setPosition(const FloatPoint& position) noexcept;

	void setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept;
	void setTilemapTexture(const sf::Texture& texture) noexcept;

	void setBackgroundColor(const sf::Color& color) noexcept;
	
	void setGridVisible(const bool visible) noexcept;

	void receiveEvents(const sf::Event& event) noexcept;

	void addOnMouseClick(OnMouseClickDelegate delegate) noexcept;
	void addOnMouseMove(OnMouseMoveDelegate delegate) noexcept;

	void build() noexcept;

	Tile getTile(const IntPoint& position) const noexcept;
	Tile getTile(const FloatPoint& position) const noexcept;
	Tile getTile(const TileIndex& index) const noexcept;

	std::vector<Tile> getTiles(const FloatArea& area) const noexcept;

	FloatPoint getTilePosition(const TileIndex& index) const noexcept;
	FloatPoint getTileCenterPosition(const TileIndex& index) const noexcept;

	float getTileWidth() const noexcept;
	float getTileHeight() const noexcept;
	const FloatSize& getTileSize() const noexcept;

	FloatArea getArea() const noexcept;

	const int getRowCount() const noexcept;
	const int getColumnCount() const noexcept;

	bool isGridVisible() const noexcept;

private:
	void setTileSprite(const Tile::Identifier tileIdentifier, const TileIndex& tileIndex) noexcept;
	void clearTileSprite(const TileIndex& tileIndex) noexcept;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2u calculateTextureTilePosition(const Tile::Identifier tileIdentifier) const noexcept;
	unsigned int calculateTextureTileIdentifierCount() const noexcept;
	
	sf::Vertex* getTileSpriteVerticles(const TileIndex& tileIndex) noexcept;

	bool isContainsPoint(const IntPoint& point) const noexcept;

	sf::Transformable mTransform;

	std::unique_ptr<Tilemap> mTilemap;

	const sf::Texture* mTilemapTexture;

	sf::Color mBackgroundColor;
	sf::VertexArray mBackgroundVerticlesArray;
	sf::VertexArray mTileVerticlesArray;

	TilemapGrid mGrid;

	std::vector<OnMouseClickDelegate> mOnMouseClickDelegates;
	std::vector<OnMouseMoveDelegate> mOnMouseMoveDelegates;
};
