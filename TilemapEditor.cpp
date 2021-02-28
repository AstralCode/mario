#include "TilemapEditor.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "ResourceContainer.hpp"

TilemapEditor::TilemapEditor(const ResourceContainer& resourceContainer) noexcept :
	mResourceContainer{resourceContainer}
{
	mTilemapGrid.setTileSize(32.0f, 32.0f);
	mTilemapGrid.setTileCount(20, 15);
	mTilemapGrid.build();
}

void TilemapEditor::initialize(const sf::Texture& texture) noexcept
{
	mTilemapPaletteView.setTilemapTexture(texture);

	const auto positionY = mTilemapGrid.getTilePosition({0, 11}).getY();

	mTilemapPaletteBorder.setPosition(6.0f, positionY);
	mTilemapPaletteBorder.setSize({32.0f * 20.0f - 12.0f, 32.0f * 4.0f - 4.0f});
	mTilemapPaletteBorder.setFillColor(sf::Color::Transparent);
	mTilemapPaletteBorder.setOutlineColor(sf::Color::White);
	mTilemapPaletteBorder.setOutlineThickness(1.0f);

	auto tilemapPalette = std::make_unique<Tilemap>(4, 4);
	tilemapPalette->getRow(0) = Tilemap::Row{1,   2,   3,   4};
	tilemapPalette->getRow(1) = Tilemap::Row{5,   6,   7,   8};
	tilemapPalette->getRow(2) = Tilemap::Row{9,  10,  11,  12};
	tilemapPalette->getRow(3) = Tilemap::Row{13,  14,  15,  16};

	mTilemapPaletteView.setTilemap(std::move(tilemapPalette));
	mTilemapPaletteView.setPosition(6.0f, positionY);
	mTilemapPaletteView.setMargins(4.0f, 4.0f, 0.0f, 0.0f);
	mTilemapPaletteView.build({32, 32});
}

void TilemapEditor::newTilemap(const int rowCount, const int columnCount) noexcept
{

}

void TilemapEditor::setTilemap(std::unique_ptr<Tilemap> tilemap) noexcept
{
	mTilemap = std::move(tilemap);
}

void TilemapEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mTilemapPaletteBorder, states);
	target.draw(mTilemapPaletteView, states);
}
