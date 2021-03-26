#pragma once

#include <map>
#include <vector>

#include "Tile.hpp"

class Tilemap final
{
public:
	using TileIdentifiers = std::vector<Tile::Identifier>;
	using TilemapIdentifiers = std::vector<TileIdentifiers>;
	using TileTraits = std::map<Tile::Identifier, Tile::Traits>;

	Tilemap(const int rowCount, const int columnCount, const FloatSize& tileSize) noexcept;

	void setTileIdentifier(const TileIndex& index, const Tile::Identifier identifier) noexcept;
	void setTileIdentifiers(const TilemapIdentifiers& identifiers) noexcept;

	void setTileColliders(const TileIdentifiers& tileIdentifiers) noexcept;

	Tile::Identifier getTileIdentifier(const TileIndex& index) const noexcept;

	Tile::Traits getTileTraits(const Tile::Identifier identifier) const noexcept;
	Tile::Traits getTileTraits(const TileIndex& index) const noexcept;

	TileIdentifiers& getRow(const int index) noexcept;
	TileIdentifiers getRow(const int index) const noexcept;

	const int getRowCount() const noexcept;
	const int getColumnCount() const noexcept;

	const FloatSize& getTileSize() const noexcept;

private:
	int mTileRowCount;
	int mTileColumnCount;

	FloatSize mTileSize;

	TilemapIdentifiers mIdentifiers;
	TileTraits mTraits;
};
