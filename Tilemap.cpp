#include "Tilemap.hpp"

Tilemap::Tilemap(const int rowCount, const int columnCount, const FloatSize& tileSize) noexcept :
	mTileRowCount{rowCount},
	mTileColumnCount{columnCount},
	mTileSize{tileSize},
	mIdentifiers(rowCount, TileIdentifiers(columnCount))
{

}

void Tilemap::setTileIdentifier(const Tile::Index& index, const Tile::Identifier identifier) noexcept
{
	mIdentifiers[index.row][index.column] = identifier;
}

void Tilemap::setTileIdentifiers(const TilemapIdentifiers& identifiers) noexcept
{
	mIdentifiers = identifiers;
}

void Tilemap::setTileColliders(const TileIdentifiers& tileIdentifiers) noexcept
{
	for (const auto identifier : tileIdentifiers)
	{
		mAttributes[identifier].set(Tile::Attributes::Collider);
	}
}

Tile::Identifier Tilemap::getTileIdentifier(const Tile::Index& index) const noexcept
{
	return mIdentifiers[index.row][index.column];
}

Tile::AttributeFlags Tilemap::getTileAttributes(const Tile::Identifier identifier) const noexcept
{
	Tile::AttributeFlags attributes{};

	const auto tileAttributesIterator = mAttributes.find(identifier);
	if (tileAttributesIterator != mAttributes.end())
	{
		attributes = tileAttributesIterator->second;
	}

	return attributes;
}

Tile::AttributeFlags Tilemap::getTileAttributes(const Tile::Index& index) const noexcept
{
	return getTileAttributes(getTileIdentifier(index));
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
