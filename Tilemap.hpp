#pragma once

#include <map>
#include <vector>

#include "Tile.hpp"

class Tilemap final
{
public:
	using Row = std::vector<Tile::Identifier>;
	using TileAttributes = std::map<Tile::Identifier, Tile::AttributeFlags>;

	Tilemap(const int rowCount, const int columnCount, const FloatSize& tileSize) noexcept;

	void setTileIdentifier(const Tile::Index& index, const Tile::Identifier identifier) noexcept;
	void setTileAttributes(const TileAttributes& attributes) noexcept;

	Tile::Identifier getTileIdentifier(const Tile::Index& index) const noexcept;

	Tile::AttributeFlags getTileAttributes(const Tile::Identifier identifier) const noexcept;
	Tile::AttributeFlags getTileAttributes(const Tile::Index& index) const noexcept;

	Row& getRow(const int index) noexcept;
	Row getRow(const int index) const noexcept;

	const int getRowCount() const noexcept;
	const int getColumnCount() const noexcept;

	const FloatSize& getTileSize() const noexcept;

private:
	int mTileRowCount;
	int mTileColumnCount;

	FloatSize mTileSize;

	std::vector<Row> mTileIdentifiers;
	TileAttributes mTileAttributes;
};
