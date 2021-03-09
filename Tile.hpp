#pragma once

#include "Flags.hpp"

using TileIdentifier = unsigned short;

struct TileIndex
{
	using ValueType = int;

	ValueType row = 0;
	ValueType column = 0;

	friend bool operator==(const TileIndex& tileA, const TileIndex& tileB)
	{
		return (tileA.row == tileB.row && tileA.column == tileB.column);
	}

	friend bool operator!=(const TileIndex& tileA, const TileIndex& tileB)
	{
		return !(tileA == tileB);
	}
};

enum class TileAttributes
{
	Collider
};

using TileAttributeFlags = Flags<TileAttributes, 1u>;
