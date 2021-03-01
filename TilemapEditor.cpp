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
	mTilemapPaletteView.setInformationText(mResourceContainer.getFont(FontIdentifiers::Roboto));

	TileIdentifier tileIdentifier = 0;

	auto tilemapPalette = std::make_unique<Tilemap>(4, 14);
	for (auto rowIndex{0}; rowIndex < tilemapPalette->getRowCount(); rowIndex++)
	{
		auto& tilemapRow = tilemapPalette->getRow(rowIndex);

		for (auto columnIndex{0}; columnIndex < tilemapPalette->getColumnCount(); columnIndex++)
		{
			tilemapRow[columnIndex] = ++tileIdentifier;
		}
	}

	const auto positionY = mTilemapGrid.getTilePosition({11, 0}).getY() - 4.0f;

	mTilemapPaletteView.setTilemap(std::move(tilemapPalette));
	mTilemapPaletteView.setPosition(4.0f, positionY);
	mTilemapPaletteView.setMargins(0.0f, 0.0f, 0.0f, 0.0f);
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
