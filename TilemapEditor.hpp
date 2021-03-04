#pragma once

#include <memory>

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "TilemapView.hpp"

class ResourceContainer;

class TilemapEditor final : public sf::Drawable
{
public:
	TilemapEditor(const ResourceContainer& resources) noexcept;

	void initialize(const sf::Texture& texture) noexcept;

	void newTilemap(const int rowCount, const int columnCount) noexcept;
	void setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::unique_ptr<Tilemap> mTilemap;

	const ResourceContainer& mResources;

	TilemapGrid mTilemapGrid;
	TilemapView mTilemapPaletteView;

	sf::RectangleShape mTilemapPaletteBorder;
};
