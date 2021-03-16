#include "TilemapEditor.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

#include "ResourceContainer.hpp"

TilemapEditor::TilemapEditor(const ResourceContainer& resources) noexcept :
	mResources{resources}
{
	mTilemapGrid.setTileSize(32, 32);
	mTilemapGrid.setTileCount(20, 15);
	mTilemapGrid.build();
}

void TilemapEditor::initialize(const sf::Texture&) noexcept
{
	TileIdentifier tileIdentifier{0};

	auto tilemapPalette = std::make_unique<Tilemap>(4, 14);
	for (auto row{0}; row < tilemapPalette->getRowCount(); row++)
	{
		auto& tilemapRow = tilemapPalette->getRow(row);

		for (auto column{0}; column < tilemapPalette->getColumnCount(); column++)
		{
			tilemapRow[column] = ++tileIdentifier;
		}
	}

	const auto positionY = mTilemapGrid.getTilePosition({11, 0}).getY() - 4.0f;

	mTilemapPaletteView.setTilemap(std::move(tilemapPalette));
	mTilemapPaletteView.setTilemapTexture(mResources.getTexture(Textures::Scenery));
	mTilemapPaletteView.setPosition(4.0f, positionY);
	mTilemapPaletteView.setMargins(0.0f, 0.0f, 0.0f, 0.0f);
	mTilemapPaletteView.build({32, 32});
}

void TilemapEditor::newTilemap(const int, const int) noexcept
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
