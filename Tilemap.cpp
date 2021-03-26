#include "Tilemap.hpp"

Tilemap::Tilemap(const int rowCount, const int columnCount, const FloatSize& tileSize) noexcept :
	mTileRowCount{rowCount},
	mTileColumnCount{columnCount},
	mTileSize{tileSize},
	mIdentifiers(rowCount, TileIdentifiers(columnCount))
{

}

void Tilemap::setTileIdentifier(const TileIndex& index, const Tile::Identifier identifier) noexcept
{
	mIdentifiers[index.getRow()][index.getColumn()] = identifier;
}

void Tilemap::setTileIdentifiers(const TilemapIdentifiers& identifiers) noexcept
{
	mIdentifiers = identifiers;
}

void Tilemap::setTileColliders(const TileIdentifiers& tileIdentifiers) noexcept
{
	for (const auto identifier : tileIdentifiers)
	{
		mTraits[identifier].set(Tile::TraitType::Collider);
	}
}

Tile::Identifier Tilemap::getTileIdentifier(const TileIndex& index) const noexcept
{
	return mIdentifiers[index.getRow()][index.getColumn()];
}

Tile::Traits Tilemap::getTileTraits(const Tile::Identifier identifier) const noexcept
{
	Tile::Traits traits{};

	const auto tileTraitsIterator = mTraits.find(identifier);
	if (tileTraitsIterator != mTraits.end())
	{
		traits = tileTraitsIterator->second;
	}

	return traits;
}

Tile::Traits Tilemap::getTileTraits(const TileIndex& index) const noexcept
{
	return getTileTraits(getTileIdentifier(index));
}

Tilemap::TileIdentifiers& Tilemap::getRow(const int index) noexcept
{
	return mIdentifiers[index];
}

Tilemap::TileIdentifiers Tilemap::getRow(const int index) const noexcept
{
	return mIdentifiers[index];
}

const int Tilemap::getRowCount() const noexcept
{
	return mTileRowCount;
}

const int Tilemap::getColumnCount() const noexcept
{
	return mTileColumnCount;
}

const FloatSize& Tilemap::getTileSize() const noexcept
{
	return mTileSize;
}
