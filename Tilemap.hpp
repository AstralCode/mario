#pragma once

#include <map>
#include <vector>
#include <optional>

#include "Tile.hpp"

class Tilemap final
{
public:
	using Row = std::vector<TileIdentifier>;

	Tilemap(const int rowCount, const int columnCount) noexcept;

	void setIdentifier(const TileIndex& index, const TileIdentifier identifier) noexcept;
	void setAttributes(const std::map<TileIdentifier, TileAttributeFlags>& attributes) noexcept;

	TileIdentifier getIdentifier(const TileIndex& index) const noexcept;

	std::optional<TileAttributeFlags> getAttributes(const TileIdentifier identifier) const noexcept;
	std::optional<TileAttributeFlags> getAttributes(const TileIndex& index) const noexcept;

	Row& getRow(const int index) noexcept;
	Row getRow(const int index) const noexcept;

	const int getRowCount() const noexcept;
	const int getColumnCount() const noexcept;

private:
	int mRowCount;
	int mColumnCount;

	std::map<TileIdentifier, TileAttributeFlags> mTileAttributes;
	std::vector<Row> mTileIdentifiers;
};
