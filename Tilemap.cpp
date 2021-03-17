#include "Tilemap.hpp"

Tilemap::Tilemap(const int rowCount, const int columnCount, const FloatSize& tileSize) noexcept :
	mTileRowCount{rowCount},
	mTileColumnCount{columnCount},
	mTileSize{tileSize},
	mTileIdentifiers(rowCount, Row(columnCount))
{

}

void Tilemap::setTileIdentifier(const Tile::Index& index, const Tile::Identifier identifier) noexcept
{
	mTileIdentifiers[index.row][index.column] = identifier;
}

void Tilemap::setTileAttributes(const TileAttributes& attributes) noexcept
{
	mTileAttributes = attributes;
}

Tile::Identifier Tilemap::getTileIdentifier(const Tile::Index& index) const noexcept
{
	return mTileIdentifiers[index.row][index.column];
}

Tile::AttributeFlags Tilemap::getTileAttributes(const Tile::Identifier identifier) const noexcept
{
	Tile::AttributeFlags attributes{};

	const auto tileAttributesIterator = mTileAttributes.find(identifier);
	if (tileAttributesIterator != mTileAttributes.end())
	{
		attributes = tileAttributesIterator->second;
	}

	return attributes;
}

Tile::AttributeFlags Tilemap::getTileAttributes(const Tile::Index& index) const noexcept
{
	return getTileAttributes(getTileIdentifier(index));
}

Tilemap::Row& Tilemap::getRow(const int index) noexcept
{
	return mTileIdentifiers[index];
}

Tilemap::Row Tilemap::getRow(const int index) const noexcept
{
	return mTileIdentifiers[index];
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
