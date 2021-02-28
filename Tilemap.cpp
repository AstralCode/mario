#include "Tilemap.hpp"

Tilemap::Tilemap(const int tileRowCount, const int tileColumnCount) noexcept :
	mRowCount{tileRowCount},
	mColumnCount{tileColumnCount},
	mTileIdentifiers(tileRowCount, std::vector<TileIdentifier>(tileColumnCount))
{

}

void Tilemap::setAttributes(const std::map<TileIdentifier, TileAttributeFlags>& attributes) noexcept
{
	mTileAttributes = attributes;
}

void Tilemap::setIdentifier(const TileIndex& index, const TileIdentifier identifier) noexcept
{
	mTileIdentifiers[index.column][index.row] = identifier;
}

std::optional<TileAttributeFlags> Tilemap::getAttributes(const TileIdentifier identifier) const noexcept
{
	std::optional<TileAttributeFlags> attributes{};

	const auto tileAttributesIterator = mTileAttributes.find(identifier);
	if (tileAttributesIterator != mTileAttributes.end())
	{
		attributes = tileAttributesIterator->second;
	}

	return attributes;
}

std::optional<TileAttributeFlags> Tilemap::getAttributes(const TileIndex& index) const noexcept
{
	return getAttributes(mTileIdentifiers[index.column][index.row]);
}

TileIdentifier Tilemap::getIdentifier(const TileIndex& index) const noexcept
{
	return mTileIdentifiers[index.column][index.row];
}

Tilemap::Row& Tilemap::getRow(const int rowIndex) noexcept
{
	return mTileIdentifiers[rowIndex];
}

Tilemap::Row Tilemap::getRow(const int rowIndex) const noexcept
{
	return mTileIdentifiers[rowIndex];
}

const int Tilemap::getRowCount() const noexcept
{
	return mRowCount;
}

const int Tilemap::getColumnCount() const noexcept
{
	return mColumnCount;
}
