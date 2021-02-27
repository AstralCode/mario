#pragma once

#include "Flags.hpp"

using TileIdentifier = unsigned short;

struct TileIndex
{
	using ValueType = int;

	ValueType row;
	ValueType column;
};

enum class TileAttributes
{
	Solid
};

using TileAttributeFlags = Flags<TileAttributes, 1u>;
